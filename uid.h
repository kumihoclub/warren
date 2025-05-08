//
// Created by rgoodson on 5/8/2025.
//

#ifndef UID_H
#define UID_H

#include <cstring>
#include <string>

#include "common.h"

namespace core {

struct UID {
    UID() : m_val{0,0,0,0} {}
    UID(const UID& other) = default;
    UID(UID&& other) noexcept = default;
    UID& operator=(const UID& other) = default;
    UID& operator=(UID&& other) noexcept = default;
    UID& operator=(const std::string& src) {
        if (src.length() > 32) return *this;
        m_val = {};
        memcpy(m_val, src.c_str(), src.length());
        return *this;
    }
    friend bool operator==(const UID &lhs, const UID &rhs) {
        return (
            lhs.m_val[0] == rhs.m_val[0] and
            lhs.m_val[1] == rhs.m_val[1] and
            lhs.m_val[2] == rhs.m_val[2] and
            lhs.m_val[3] == rhs.m_val[3]
        );
    }
    friend bool operator!=(const UID &lhs, const UID &rhs) {
        return !(lhs == rhs);
    }
private:
    u64 m_val[4];
};

}

#endif //UID_H
