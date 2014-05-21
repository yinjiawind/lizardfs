#pragma once

#include "config.h"

#include <iostream>

#include "common/chunk_type.h"
#include "common/chunk_with_version_and_type.h"
#include "common/packet.h"
#include "common/serialization_macros.h"

namespace cstoma {
inline void overwriteStatusField(std::vector<uint8_t>& destination, uint8_t status) {
	// 9 - sizeof chunkId + chunkType, 1 - sizeof status
	uint32_t statusOffset = PacketHeader::kSize + serializedSize(PacketVersion()) + 9;
	sassert(destination.size() >= statusOffset + 1);
	destination[PacketHeader::kSize + sizeof(PacketVersion) + 9] = status;
}
} // namespace cstoma

LIZARDFS_DEFINE_PACKET_SERIALIZATION(
		cstoma, chunkNew, LIZ_CSTOMA_CHUNK_NEW, 0,
		std::vector<ChunkWithVersionAndType>, chunks)

LIZARDFS_DEFINE_PACKET_SERIALIZATION(
		cstoma, registerHost, LIZ_CSTOMA_REGISTER_HOST, 0,
		uint32_t, ip,
		uint16_t, port,
		uint16_t, timeout,
		uint32_t, csVersion)

LIZARDFS_DEFINE_PACKET_SERIALIZATION(
		cstoma, registerChunks, LIZ_CSTOMA_REGISTER_CHUNKS, 0,
		std::vector<ChunkWithVersionAndType>, chunks)

LIZARDFS_DEFINE_PACKET_SERIALIZATION(
		cstoma, registerSpace, LIZ_CSTOMA_REGISTER_SPACE, 0,
		uint64_t, usedSpace,
		uint64_t, totalSpace,
		uint32_t, chunkCount,
		uint64_t, tdUsedSpace,
		uint64_t, toDeleteTotalSpace,
		uint32_t, toDeleteChunksNumber)

LIZARDFS_DEFINE_PACKET_SERIALIZATION(
		cstoma, setVersion, LIZ_CSTOMA_SET_VERSION, 0,
		uint64_t,  chunkId,
		ChunkType, chunkType,
		uint8_t,   status)

LIZARDFS_DEFINE_PACKET_SERIALIZATION(
		cstoma, deleteChunk, LIZ_CSTOMA_DELETE_CHUNK, 0,
		uint64_t,  chunkId,
		ChunkType, chunkType,
		uint8_t,   status)

LIZARDFS_DEFINE_PACKET_SERIALIZATION(
		cstoma, createChunk, LIZ_CSTOMA_CREATE_CHUNK, 0,
		uint64_t,  chunkId,
		ChunkType, chunkType,
		uint8_t,   status)

LIZARDFS_DEFINE_PACKET_SERIALIZATION(
		cstoma, truncate, LIZ_CSTOMA_TRUNCATE, 0,
		uint64_t,  chunkId,
		ChunkType, chunkType,
		uint8_t,   status)

LIZARDFS_DEFINE_PACKET_SERIALIZATION(
		cstoma, duplicateChunk, LIZ_CSTOMA_DUPLICATE_CHUNK, 0,
		uint64_t,  chunkId,
		ChunkType, chunkType,
		uint8_t,   status)

LIZARDFS_DEFINE_PACKET_SERIALIZATION(
		cstoma, duptruncChunk, LIZ_CSTOMA_DUPTRUNC_CHUNK, 0,
		uint64_t,  chunkId,
		ChunkType, chunkType,
		uint8_t,   status)

LIZARDFS_DEFINE_PACKET_SERIALIZATION(
		cstoma, replicateChunk, LIZ_CSTOMA_REPLICATE_CHUNK, 0,
		uint64_t,  chunkId,
		ChunkType, chunkType,
		uint8_t,   status, // status has to be third field to make overwriteStatusField work!!!
		uint32_t,  chunkVersion)