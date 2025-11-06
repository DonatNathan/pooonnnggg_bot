#include "memory.hpp"

ReplayBuffer::ReplayBuffer(size_t capacity) : capacity(capacity)
{

};

void ReplayBuffer::push(const Transition &t)
{
    if (buf.size() < capacity) buf.push_back(t);
    else {
        buf[pos] = t;
        pos = (pos + 1) % capacity;
    }
};

std::vector<Transition> ReplayBuffer::sample(size_t n)
{
    std::vector<Transition> out; out.reserve(n);
    std::uniform_int_distribution<size_t> dist(0, buf.size()-1);
    for (size_t i=0;i<n;i++) out.push_back(buf[dist(rng)]);
    return out;
};

size_t ReplayBuffer::size()
{
    return buf.size();
};
