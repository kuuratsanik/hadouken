#ifndef HADOUKEN_BITTORRENT_TORRENTHANDLE_HPP
#define HADOUKEN_BITTORRENT_TORRENTHANDLE_HPP

#include <libtorrent/torrent_handle.hpp>
#include <string>

namespace Hadouken
{
    namespace BitTorrent
    {
        struct TorrentStatus;

        struct TorrentHandle
        {
            explicit TorrentHandle(const libtorrent::torrent_handle& handle);

            std::string getInfoHash() const;

            int getQueuePosition() const;

            TorrentStatus getStatus() const;

            bool isValid() const;
            
            void pause() const;

            void resume() const;

        private:
            const libtorrent::torrent_handle handle_;
        };
    }
}

#endif
