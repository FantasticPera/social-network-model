#ifndef NodeList_h
#define NodeList_h

template <typename T>
struct NodeList {
    NodeList* next;
    T info;
    NodeList(T info) : info(info), next(nullptr) {}
};


#endif
