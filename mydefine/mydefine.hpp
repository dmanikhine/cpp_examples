#pragma once

#define DISALLOW_COPY_AND_ASSIGN(TypeName)  \
    TypeName(const TypeName &src) = delete; \
    TypeName &operator=(const TypeName &rhs) = delete;