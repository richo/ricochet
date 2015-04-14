#!/usr/bin/env python
import os
import sys

sys.path.insert(0, "protobufs")

import AuthHiddenService_pb2 as AuthHiddenService
import ChatChannel_pb2 as ChatChannel
import ContactRequestChannel_pb2 as ContactRequestChannel
import ControlChannel_pb2 as ControlChannel

import random

def generator(l, func):
    return ''.join(func() for _ in range(l))

def random_bytes():
    return chr(int(random.random() * 256))

def random_char():
    return chr(int(random.random() * 94) + 32)

def build_testcase(prefix):
    def _(name):
        return open(os.path.join(prefix, name), "wb")
    return _

# def msg():
#     pkt = ChatChannel.Packet()
#     msg = pkt.ChatMessage()
#     pkt.chat_message = msg
#     return pkt

# def ack():
#     pkt = ChatChannel.Packet()
#     ack = ChatChannel.ChatAcknowledge()
#     pkt.chat_acknowledge = ack
#     return pkt

# def broken_ack():
#     pkt = ChatChannel.Packet()
#     ack = ChatChannel.ChatAcknowledge()
#     pkt.chat_message = ack
#     return pkt

# def broken_msg():
#     pkt = ChatChannel.Packet()
#     msg = ChatChannel.ChatMessage()
#     pkt.chat_acknowledge = msg
#     return pkt

def rand_uint32():
    return int(random.random() * (1 << 32))

def rand_int64():
    v = random.random() - .5
    return int(v * (1 << 64))


def main():
    # Build some really naive testcases for chat
    testcase = build_testcase("testcases")

    for i in range(6):
        with testcase("less_garbage_msg_%d" % i) as fh:
            pkt = ChatChannel.Packet()
            msg = pkt.chat_message
            # TODO: Manually munge invalid utf8 in here
            msg.message_text = generator(256, random_char)
            if random.random() > 0.5:
                msg.message_id = rand_uint32()
            if random.random() > 0.5:
                msg.time_delta = rand_int64()
            fh.write(pkt.SerializeToString())
    for i in range(6):
        with testcase("less_garbage_ack_%d" % i) as fh:
            pkt = ChatChannel.Packet()
            ack = pkt.chat_acknowledge
            # TODO: Manually munge invalid utf8 in here
            ack.message_id = rand_uint32()
            if random.random() > 0.5:
                ack.accepted = False
            fh.write(pkt.SerializeToString())

if __name__ == '__main__':
    main()
