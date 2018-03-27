using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace MultiMedia
{
	internal sealed class LibraryImage
	{
		internal readonly string OriginalPath;

		internal bool ThumbnailChecked;
		internal string ThumbnailPath;

		internal BitmapSource ThumbnailImage;
		internal bool ExceptionedAndIgnored;

		internal LibraryImage(string path)
		{
			OriginalPath = path;
			ThumbnailChecked = false;
			ThumbnailPath = Path.GetDirectoryName(OriginalPath) + "\\Thumbnail\\" + Path.GetFileName(OriginalPath);

			ExceptionedAndIgnored = false;
		}

		internal double CurrentCompareValue;

		public override string ToString()
			=> OriginalPath;
	}
}
