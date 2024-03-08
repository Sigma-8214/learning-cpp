#pragma once

// todo: figure out what the virtual methods are about...

namespace list {
template <class T> class List {
  public:
    /** Sees whether this list is empty.
    @return True if the list is empty; otherwise returns false. */
    virtual bool isEmpty() const = 0;

    /** Gets the current number of entries in this list.
    @return The integer number of entries currently in the list. */
    virtual int getLength() const = 0;

    /** Inserts an entry into this list at a given position.
    @pre None.
    @post If 0 <= position <= getLength() and the insertion is
    successful, newEntry is at the given position in the list,
    other entries are renumbered accordingly, and the returned
    value is true.
    @param newPosition The list position at which to insert newEntry.
    @param newEntry The entry to insert into the list.
    @return True if insertion is successful, or false if not. */
    virtual bool insert(int newPosition, const T &newEntry) = 0;

    /** Removes the entry at a given position from this list.
    @pre None.
    @post If 0 <= position < getLength() and the removal is successful,
    the entry at the given position in the list is removed, other
    items are renumbered accordingly, and the returned value is true.
    @param position The list position of the entry to remove.
    @return True if removal is successful, or false if not. */
    virtual bool remove(int position) = 0;

    /** Removes all entries from this list.
    @post List contains no entries and the count of items is 0. */
    virtual void clear() = 0;

    /** Gets the entry at the given position in this list.
    @pre 0 <= position < getLength().
    @post The desired entry has been returned.
    @param position The list position of the desired entry.
    @return The entry at the given position. */
    virtual T getEntry(int position) const = 0;

    /** Replaces the entry at the given position in this list.
    @pre 0 <= position < getLength().
    @post The entry at the given position is newEntry.
    @param position The list position of the entry to replace.
    @param newEntry The replacement entry. */
    virtual void setEntry(int position, const T &newEntry) = 0;
};

template <class T> class ArrayList : public List<T> {
    size_t size;
    size_t capacity;
    T *data;

    void resize(size_t size);

  public:
    static ArrayList empty();

    bool isEmpty() const;
    int getLength() const;
    bool insert(int newPosition, const T &newEntry);
    bool remove(int position);
    void clear();
    T getEntry(int position) const;
    void setEntry(int position, const T &newEntry);

    void swap(int a, int b);
};

template <class T> class LinkedList : public List<T> {
    struct Node {
        T data;
        Node *next;
    };

    Node *head;
    size_t size;

  public:
    static LinkedList empty();

    bool isEmpty() const;
    int getLength() const;
    bool insert(int newPosition, const T &newEntry);
    bool remove(int position);
    void clear();
    T getEntry(int position) const;
    void setEntry(int position, const T &newEntry);
};

} // namespace list

#include "list.cpp"