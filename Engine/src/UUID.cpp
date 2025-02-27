#include "ltbpch.h"
#include "UUID.h"

#include "config.h"

#include <random>

#include <unordered_map>

namespace LTB {

	UUID::UUID()
		: m_UUID(RandomU64())
	{
	}

	UUID::UUID(uint64_t uuid)
		: m_UUID(uuid)
	{
	}

}
