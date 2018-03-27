using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace MethodQualityEvaluation
{
	public static class NativeMethods
	{
		// public const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1sift.dll";
		// public const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1rgb.dll";
		// public const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1phash.dll";
		// public const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1hsv.dll";
		// public const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1all1.dll";
		// public const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1all2.dll";
		// public const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1all3.dll";
		public const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1all4.dll";

		[DllImport(DLLPath)]
		public static extern int PrepareCompare(IntPtr path);

		[DllImport(DLLPath)]
		public static extern double Compare(IntPtr patternPath, IntPtr sourcePath);

		// safe interface
		public static int PrepareCompare(string path)
			=> PrepareCompare(Marshal.StringToHGlobalAnsi(path));

		public static double Compare(string pattern, string source)
			=> Compare(Marshal.StringToHGlobalAnsi(pattern), Marshal.StringToHGlobalAnsi(source));
	}

	internal class Program
	{
		private const string ImageLibPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\TestFiles\";

		private static void MainProcess()
		{
			var imagePaths =
				from file in Directory.EnumerateFiles(ImageLibPath, "*.*")
				where file.EndsWith(".bmp") || file.EndsWith(".jpg")
				select file;

			Dictionary<string, List<string>> groups = new Dictionary<string, List<string>>
			{
				["white"] = new List<string>(),
				["xg"] = new List<string>(),
				["yello"] = new List<string>(),
				["red"] = new List<string>(),
				["pt"] = new List<string>(),
				["cat"] = new List<string>(),
				["dog"] = new List<string>(),
			};
			foreach (var image in imagePaths)
			{
				var fileName = Path.GetFileName(image);
				foreach (var groupName in groups.Keys)
				{
					if (fileName.StartsWith(groupName))
						groups[groupName].Add(image);
				}
			}

			Dictionary<string, string> randomSources = new Dictionary<string, string>
			{
				["white"] = null,
				["xg"] = null,
				["yello"] = null,
				["red"] = null,
				["pt"] = null,
				["cat"] = null,
				["dog"] = null,
			};
			Random random = new Random();
			foreach (var group in groups)
			{
				var next = random.Next(0, group.Value.Count);
				randomSources[group.Key] = group.Value[next];
			}

			Console.OpenStandardOutput();
			using (var stream = File.Create(Path.GetFileNameWithoutExtension(NativeMethods.DLLPath) + ".log"))
			{
				using (var writer = new StreamWriter(stream))
				{
					writer.WriteLine("Log for " + Path.GetFileNameWithoutExtension(NativeMethods.DLLPath));

					int hr = NativeMethods.PrepareCompare(ImageLibPath);
					writer.WriteLine("Prepare compare returned " + hr);
					if (hr != 0)
					{
						writer.WriteLine("exited");
						return;
					}

					List<double> sourceAverageRanks = new List<double>();
					for (int i = 0; i < randomSources.Keys.Count; ++i)
					{
						writer.WriteLine("\ttest " + i + ": ");
						Console.Error.WriteLine("\ttest " + i + ": ");

						foreach (var pattern in randomSources)
						{
							writer.WriteLine("\t\tPattern: " + Path.GetFileName(pattern.Value));
							Console.Error.WriteLine("\t\tPattern: " + Path.GetFileName(pattern.Value));
							List<double> results = new List<double>();
							foreach (var source in imagePaths)
							{
								//if (source != pattern.Value)
								//{
								double res = NativeMethods.Compare(pattern.Value, source);
								results.Add(res);
								//}
							}
							List<Tuple<string, double>> resultSourcePairs = new List<Tuple<string, double>>();
							for (int j = 0; j < imagePaths.Count(); ++j)
							{
								resultSourcePairs.Add(Tuple.Create(imagePaths.ElementAt(j), results[j]));
							}
							resultSourcePairs = resultSourcePairs.OrderBy(pair => pair.Item2).ToList();

							List<int> ranks = new List<int>();
							for (int j = 0; j < resultSourcePairs.Count(); ++j)
							{
								var resultSourcePair = resultSourcePairs.ElementAt(j);
								writer.Write("\t\t\tSource: " + Path.GetFileName(resultSourcePair.Item1) + ", value: " + resultSourcePair.Item2
									+ " with rank: " + j);

								bool isMember = false;
								foreach (var groupMember in groups[pattern.Key])
								{
									if (resultSourcePairs.ElementAt(j).Item1 == groupMember && j != 0)
									{
										isMember = true;
										ranks.Add(j);
										break;
									}
								}
								if (isMember)
								{
									writer.WriteLine(", Is group member");
								}
								else
								{
									writer.WriteLine("");
								}
							}

							// should be large than 1, more close to 1 is better, smaller than 1 is perfect
							var average = ranks.Average();
							writer.WriteLine("\t\tAverage rank is " + average);
							Console.Error.WriteLine("\t\tAverage rank is " + average);
							sourceAverageRanks.Add(average);
						}
					}

					var allAverage = sourceAverageRanks.Average();
					writer.WriteLine("\tFinal result: " + allAverage);
					Console.Error.WriteLine("\tFinal result: " + allAverage);
				}
			}

			// Console.ReadLine();
		}

		private static void ProcessResult()
		{
			string[] dllPaths =
			{
				@"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1sift.dll",
				@"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1rgb.dll",
				@"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1phash.dll",
				@"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1hsv.dll",
				@"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1all1.dll",
				@"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1all2.dll",
				@"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1all3.dll",
				@"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1all4.dll",
			};

			List<List<string>> groups = new List<List<string>>
			{
				new List<string> { "cat3.bmp" },
				new List<string> { "dog6.bmp" },
				new List<string> { "dog7.bmp" },
				new List<string> { "pt1.jpg", "pt2.jpg", "pt4.jpg", "pt5.jpg", "pt6.jpg", "pt7.jpg", },
				new List<string> { "cat1.bmp", "white1.bmp", "white2.bmp", "white3.bmp", "white4.bmp", "white5.bmp", "white6.bmp", "white7.bmp", "white8.bmp", "white9.bmp", "white10.bmp", },
				new List<string> { "yellow1.bmp", "yellow2.bmp", "yellow3.bmp", "yellow4.bmp", "yellow5.bmp", "yellow6.bmp", "yellow7.bmp", "yellow8.bmp", "yellow9.bmp", "yellow10.bmp", },
				new List<string> { "red1.bmp", "red2.bmp", "red3.bmp", "red4.bmp", "red5.bmp", "red6.bmp", "red7.bmp", "red8.bmp", "red9.bmp", "red10.bmp", },
				new List<string> { "xg3.bmp", "xg4.bmp" },
			};

			using (var outputStream = File.Create("MultiMedia.log"))
			{
				using (var outputWriter = new StreamWriter(outputStream))
				{
					foreach (var dllPath in dllPaths)
					{
						// pattern, source, rank
						List<Tuple<string, string, int>> patternSourcePairs = new List<Tuple<string, string, int>>();
						using (var stream = File.OpenRead(Path.GetFileNameWithoutExtension(dllPath) + ".log"))
						{
							using (var reader = new StreamReader(stream))
							{
								string currentLine = reader.ReadLine();
								string currentPattern = "";
								while (currentLine != null)
								{
									currentLine = currentLine.Trim();
									if (currentLine.StartsWith("Pattern: "))
									{
										currentPattern = currentLine.Substring(9);
									}
									else if (currentLine.StartsWith("Source: "))
									{
										int firstCommaIndex = currentLine.IndexOf(',');
										var sourceName = currentLine.Substring(8, firstCommaIndex - 8);

										int lastColonIndex = currentLine.LastIndexOf(':');
										var rankString = currentLine.Substring(lastColonIndex + 2);

										if (rankString.EndsWith(", Is group member"))
										{
											rankString = rankString.Substring(0, rankString.Length - 17);
										}

										int rank = -1;
										Int32.TryParse(rankString, out rank);
										if (currentPattern != sourceName)
										{
											patternSourcePairs.Add(Tuple.Create(currentPattern, sourceName, rank));
										}
									}
									currentLine = reader.ReadLine();
								}
							}
						}

						var ranks = new List<int>();
						foreach (var patternSourcePair in patternSourcePairs)
						{
							bool isInSameGroup = false;
							foreach (var group in groups)
							{
								bool sourceHere = false;
								bool patternHere = false;
								foreach (var item in group)
								{
									if (patternSourcePair.Item1 == item)
									{
										sourceHere = true;
									}
									if (patternSourcePair.Item2 == item)
									{
										patternHere = true;
									}
								}
								if (sourceHere && patternHere)
								{
									isInSameGroup = true;
									break;
								}
							}
							if (isInSameGroup)
							{
								ranks.Add(patternSourcePair.Item3);
							}
						}
						outputWriter.WriteLine(Path.GetFileNameWithoutExtension(dllPath) + ": " + ranks.Average());
					}
				}
			}
		}

		private static void Main()
		{
			ProcessResult();
		}
	}
}
