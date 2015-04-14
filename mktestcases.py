#!/usr/bin/env python
import os
import sys

sys.path.insert(0, "protobufs")

import AuthHiddenService_pb2 as AuthHiddenService
import ChatChannel_pb2 as ChatChannel
import ContactRequestChannel_pb2 as ContactRequestChannel
import ControlChannel_pb2 as ControlChannel

def gen_testcases(klass, out_dir):
    # Really dumb test data to get this thing off the ground
    name = klass.__name__
    empty = klass()

    with open(os.path.join(out_dir, "%s_empty" % name), "wb") as fh:
        fh.write(empty.SerializeToString())

def main():
    for i in [ChatChannel.Packet, ContactRequestChannel.ContactRequest]:
        gen_testcases(i, "testcases")


if __name__ == '__main__':
    main()
