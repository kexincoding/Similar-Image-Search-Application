using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace MultiMedia
{
	public static class NativeMethods
	{
		// private const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1.dll";
		// private const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1hsv.dll";
		// private const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1rgb2.dll";
		// private const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1sisf(2).dll";
		// private const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1phash.dll";
		// public const string DLLPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\x64\Release\photosearch1all1.dll";
		private const string DLLPath = "CompareCore.dll";

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
}
