#pragma once

#define NUM_ATTR_WITH_GET(type, name) \
private: \
    type name; \
public: \
    type get_##name() const {return name;}; \
private:

#define NUM_ATTR_WITH_GET_AND_SET(type, name) \
private: \
    type name; \
public: \
    type get_##name() const {return name;}; \
    void set_##name(type value) {name = value;}; \
private:
