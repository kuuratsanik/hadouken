﻿using System.IO;
using Hadouken.Common;
using Hadouken.Common.IO;
using Ragnar;

namespace Hadouken.Core.BitTorrent
{
    public class TorrentInfoSaver : ITorrentInfoSaver
    {
        private readonly IEnvironment _environment;
        private readonly IFileSystem _fileSystem;

        public TorrentInfoSaver(IEnvironment environment,
            IFileSystem fileSystem)
        {
            _environment = environment;
            _fileSystem = fileSystem;
        }

        public void Save(TorrentInfo info)
        {
            var torrentsPath = _environment.GetApplicationDataPath().Combine("Torrents");

            using (var creator = new TorrentCreator(info))
            {
                var data = creator.Generate();
                var filePath = torrentsPath.CombineWithFilePath(string.Format("{0}.torrent", info.InfoHash));
                var file = _fileSystem.GetFile(filePath);

                using (var fileStream = file.Open(FileMode.Create, FileAccess.Write, FileShare.None))
                {
                    fileStream.Write(data, 0, data.Length);
                }
            }
        }
    }
}