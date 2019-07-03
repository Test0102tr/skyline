#include <sys/mman.h>
#include <syslog.h>
#include <vector>
#include "memory.h"

namespace core::memory {
    /*std::vector<MemoryRegion> memoryRegions;

    bool Map(uint64_t address, size_t size, std::string label) {
        void* ptr = mmap((void*)(address), size, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, 0, 0);
        if (!ptr) {
            syslog(LOG_ERR, "Failed mapping region '%s'", label.c_str());
            return false;
        }

        syslog(LOG_INFO, "Mapping region '%s' to 0x%x, pointer %x", label.c_str(), address, (uint64_t)ptr);

        if (core::cpu::MapUnicorn(address, size, ptr)) return false;

        syslog(LOG_INFO, "Successfully mapped region '%s' to 0x%x", label.c_str(), address);

        memoryRegions.push_back({label, address, size, ptr});
        return true;
    }*/

    // TODO: Boundary checks
    void Write(void* data, uint64_t offset, size_t size) { std::memcpy((void*)(offset), data, size); }

    void WriteU8(uint8_t value, uint64_t offset) { Write(reinterpret_cast<void*>(&value), offset, 1); }
    void WriteU16(uint16_t value, uint64_t offset) { Write(reinterpret_cast<void*>(&value), offset, 2); }
    void WriteU32(uint32_t value, uint64_t offset) { Write(reinterpret_cast<void*>(&value), offset, 4); }
    void WriteU64(uint64_t value, uint64_t offset) { Write(reinterpret_cast<void*>(&value), offset, 8); }

    void Read(void* destination, uint64_t offset, size_t size) { std::memcpy(destination, (void*)(offset), size); }

    uint8_t ReadU8(uint64_t offset) { uint8_t value; Read(reinterpret_cast<void*>(&value), offset, 1); return value; }
    uint16_t ReadU16(uint64_t offset) { uint16_t value; Read(reinterpret_cast<void*>(&value), offset, 2); return value; }
    uint32_t ReadU32(uint64_t offset) { uint32_t value; Read(reinterpret_cast<void*>(&value), offset, 4); return value; }
    uint64_t ReadU64(uint64_t offset) { uint64_t value; Read(reinterpret_cast<void*>(&value), offset, 8); return value; }
}