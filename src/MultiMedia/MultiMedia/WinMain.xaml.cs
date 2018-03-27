using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media.Imaging;

namespace MultiMedia
{
	using Fresky;
	using Fresky.IO;
	using Fresky.Resource;
	using Fresky.UI.Imaging;

	public partial class WinMain : Window
	{
		#region Constructor
		private readonly string[] ValidExtensions = { ".jpg", ".jpeg", ".png", "gif", "bmp", "tiff" };

		public WinMain()
		{
			Ures.Init();
			InitializeComponent();

			// For test
			m_SourceFilePath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\TestFiles\pt2.jpg";
			tbxSourceFile.Text = "Pattern: " + m_SourceFilePath;
			m_SourceDirectoryPath = @"C:\Users\fretmp\OneDrive\Pro\VSE\Homeworks\MultiMedia\TestFiles";
			tbxSourceDir.Text = "Lib directory: " + m_SourceDirectoryPath;
		}
		#endregion
		
		#region Title
		private void spTitle_MouseDown(Object sender, MouseButtonEventArgs e)
		{
			try { DragMove(); }
			finally { }
		}

		private void bMini_Click(Object sender, RoutedEventArgs e)
		{
			WindowState = WindowState.Minimized;
		}
		private void bMaxi_Click(Object sender, RoutedEventArgs e)
		{
			WindowState = WindowState == WindowState.Maximized ? WindowState.Normal : WindowState.Maximized;
		}
		private void bClose_Click(Object sender, RoutedEventArgs e)
		{
			Close();
		}
		private void Window_Closing(Object sender, CancelEventArgs e)
		{
			e.Cancel = MessageBox.Show("Quit application?", "MultiMedia", MessageBoxButton.YesNo) != MessageBoxResult.Yes;
		}
		#endregion

		#region Source directory and file
		private string m_SourceFilePath;
		private BitmapSource m_SourceFileImage;
		private void tbxSourceFile_MouseDown(Object sender, MouseButtonEventArgs e)
		{
			var result = FileDialog.OpenFileDialog(m_SourceFilePath);
			if (result != "")
			{
				tbxSourceFile.Text = "Pattern: " + result;
				m_SourceFilePath = result;

				if (File.Exists(m_SourceFilePath))
				{
					m_SourceFileImage = ImageSourceExt.Load(m_SourceFilePath);
					iSourceFile.Source = m_SourceFileImage;
				}
			}
			else
			{
				tbxSourceFile.Text = "";
			}
		}
		
		internal string m_SourceDirectoryPath;
		private List<LibraryImage> m_LibraryImages = new List<LibraryImage>();
		private void tbxSourceDir_MouseDown(Object sender, MouseButtonEventArgs e)
		{
			var result = FileDialog.OpenFolderDialog(m_SourceDirectoryPath == "" ? null : m_SourceDirectoryPath);
			if (result != "")
			{
				tbxSourceDir.Text = "Lib directory: " + result;
				m_SourceDirectoryPath = result;

				if (Directory.Exists(result))
				{
					HasMakePreview = false;
					m_LibraryImages.Clear();

					(from file in Directory.EnumerateFiles(result, "*.*")
					 where (
						from extension in ValidExtensions
						where file.EndsWith(extension, true, CultureInfo.CurrentCulture)
						select extension
					 ).Count() != 0
					 select file).ForEach(path => m_LibraryImages.Add(new LibraryImage(path)));
					MakeDirectoryPreview();
					pgrPreview.Max = m_LibraryImages.Count;
					pgrPreview.ValueWithEvent = 1;
				}
			}
			else
			{
				tbxSourceDir.Text = "";
			}
		}
		
		// Open
		private void bOpenSourceFile_Click(Object sender, RoutedEventArgs e)
		{
			if (File.Exists(m_SourceFilePath))
			{
				Process.Start(m_SourceFilePath);
			}
		}
		private void bOpenSourceDir_Click(Object sender, RoutedEventArgs e)
		{
			if (Directory.Exists(m_SourceDirectoryPath))
			{
				Process.Start(m_SourceDirectoryPath);
			}
		}
		#endregion

		#region Preview
		// preview dir
		private bool HasMakePreview = false;
		/// <summary>
		/// Assume .\Thumbnail same name file is the thumbnail
		/// if not created, create, if exception throw and ignore and warning some load error
		/// if created, try load, if exception then create new one
		/// load success and that is
		/// </summary>
		private void MakeDirectoryPreview()
		{
			if (HasMakePreview)
				return;

			foreach (var libImage in m_LibraryImages)
			{
				if (libImage.ThumbnailChecked)
					continue;

				bool needToConstruct = true;
				if (File.Exists(libImage.ThumbnailPath))
				{
					try
					{
						libImage.ThumbnailImage = ImageSourceExt.Load(libImage.ThumbnailPath);
						needToConstruct = false;
					}
					catch
					{
						// Load failed, change path to another path to prevent overwrite
						libImage.ThumbnailPath = PathEx.ChangeFileName(libImage.ThumbnailPath, fileName => fileName
							+ "A_very_long_name_that_definitely_would_not_collide" 
							// _because_I_dont_want_to_write_too_more_for_this_kind_of_homework_level_project"
							);
					}
				}

				if (needToConstruct)
				{
					try
					{
						if (!Directory.Exists(Path.GetDirectoryName(libImage.ThumbnailPath)))
							Directory.CreateDirectory(Path.GetDirectoryName(libImage.ThumbnailPath));

						ImageSourceExt.GetThumbnailImage(libImage.OriginalPath, libImage.ThumbnailPath, 0.1, 200, 200);
						libImage.ThumbnailImage = ImageSourceExt.Load(libImage.ThumbnailPath);
					}
					catch (Exception e)
					{
						e.ToString();
						// Still construct or load or save failed
						// give warning and ignore this
						libImage.ExceptionedAndIgnored = true;
					}
				}
			}

			StringBuilder sb = new StringBuilder("Error loading these images, they are ignored then: \n");
			bool hasAnyInvalid = false;
			foreach (var libImage in m_LibraryImages.FindAll(image => image.ExceptionedAndIgnored))
			{
				sb.Append("\t");
				sb.Append(libImage);
				sb.Append(Environment.NewLine);
				hasAnyInvalid = true;
			}

			if (hasAnyInvalid)
			{
				MessageBox.Show(sb.ToString(), "Warning");
				m_LibraryImages.RemoveAll(image => image.ExceptionedAndIgnored);
			}

			HasMakePreview = true;
		}
		
		// pager
		private void pgrPreview_ValueChanged(Object sender, ChangedEventArgs<Int32> e)
		{
			// Attention, e.NewValue from 1 to Count
			if (e.NewValue - 1 < m_LibraryImages.Count && e.NewValue > 0)
			{
				imgPreview2.Source = m_LibraryImages[e.NewValue - 1].ThumbnailImage;
			}

			var fileName = Path.GetFileName(m_LibraryImages[e.NewValue - 1].OriginalPath);
			var value = m_MaxValue - m_LibraryImages[e.NewValue - 1].CurrentCompareValue;
			tbHint.Text = (fileName.Length > 15 ? PathEx.ChangeFileName(fileName, name => name.Substring(0, 10) + "...") : fileName)
				+ ", Similarity: " + (value == 0 ? "Unknown" : value.ToString());
		}
		#endregion

		#region Compare core
		private double m_MaxValue;
		private async void bGo_Click(Object sender, RoutedEventArgs e)
		{
			bGo.IsEnabled = false;
			tbHint.Text = "Processing...";
			if (NativeMethods.PrepareCompare(m_SourceDirectoryPath) != 0)
			{
				MessageBox.Show("Compare pre operation failed, following operations may be incorrect");
			}
			
			await Task.Run(() =>
			{
				int index = 0;
				foreach (var libImage in m_LibraryImages)
				{
					Dispatcher.Invoke(() => { tbHint.Text = $"Procssing...({index}/{m_LibraryImages.Count})"; });
					libImage.CurrentCompareValue = NativeMethods.Compare(m_SourceFilePath, libImage.OriginalPath);
					++index;
				}
			});

			m_LibraryImages = m_LibraryImages.OrderBy(libImage => libImage.CurrentCompareValue).ToList();
			m_MaxValue = m_LibraryImages.Max(libImage => libImage.CurrentCompareValue);
			pgrPreview.ValueWithEvent = 1;
			bGo.IsEnabled = true;
		}
		#endregion
	}
}
