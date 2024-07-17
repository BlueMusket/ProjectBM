#pragma once

typedef int PeerId_t;
static const PeerId_t DEFAULT_PEER_ID = 0;


enum PeerRefType
{
    PEER_REF_TYPE_RECV = 0,
    PEER_REF_TYPE_SEND,
    PEER_REF_TYPE_SHARD,
    PEER_REF_TYPE_MAX
};