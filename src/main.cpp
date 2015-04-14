/* Ricochet - https://ricochet.im/
 * Copyright (C) 2014, John Brooks <john.brooks@dereferenced.net>
 *
 * Author: Richo Healey <richo@psych0tik.net>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other materials provided with the
 *      distribution.
 *
 *    * Neither the names of the copyright owners nor the names of its
 *      contributors may be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <unistd.h>
#include <iostream>
#include "ui/MainWindow.h"
#include "core/IdentityManager.h"
#include "tor/TorManager.h"
#include "tor/TorControl.h"
#include "utils/CryptoKey.h"
#include "utils/SecureRNG.h"
#include "utils/Settings.h"
#include "protocol/Channel.h"
#include "protocol/ChatChannel.h"
#include "protocol/ContactRequestChannel.h"
/* #include "protocol/ControlChannel.h" */
#include <QApplication>
#include <QIcon>
#include <QLibraryInfo>
#include <QSettings>
#include <QTime>
#include <QDir>
#include <QTranslator>
#include <QMessageBox>
#include <QLocale>
#include <QLockFile>
#include <QStandardPaths>
#include <openssl/crypto.h>

void usage(char *argv[]) {
    std::cout << "Usage: " << argv[0] << " <channel type> <input file>" << std::endl;
    std::cout << "  Channel types: chat, contactrequest" << std::endl;
}

int main(int argc, char *argv[])
{
    Protocol::Channel *channel;
    if (argc != 3) {
        usage(argv);
        return 1;
    }

    if (strcmp(argv[1], "chat") == 0) {
        channel = new Protocol::ChatChannel(Protocol::Channel::Inbound, NULL);
    } else if (strcmp(argv[1], "contactrequest") == 0) {
        channel = new Protocol::ContactRequestChannel(Protocol::Channel::Inbound, NULL);
    /* } else if (strcmp(argv[1], "control") == 0) { */
    /*     channel = new Protocol::ControlChannel(Protocol::Channel::Inbound, NULL); */
    } else {
        usage(argv);
        return 1;
    }

    FILE *fh = fopen(argv[2], "r");
    if (fh == NULL) {
        std::cerr << "couldn't open " << argv[2] << std::endl;
        return 1;
    }

    QFile f;
    f.open(fh, QIODevice::ReadOnly);
    QByteArray ba = f.readAll();

    channel->receivePacket(ba);

    return 0;
}
