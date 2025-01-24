#define MAX_PAGES_IN_MEM 262144 // that is the size of the memory (4GB) / the size of the page (4KB)

//-----------------------------------------------------------------
//                          LRU
//-----------------------------------------------------------------

// first we will implement LRU algorithm
// LRU uses a doubly linked list of pages
// the front of the list is the least recently used page, 
// and in the back is the most recently used page
struct page {
    int pageno;
    struct page *next, *prev;
};


void lru_add_page(struct page *new_page) {
    assert(new_page);
    if (!lru) {
        mru = lru = new_page;
        return;
    }

    // Basic linked list insertion
    // The new page will be inserted in the back because it is the most recently used
    mru->next = new_page;
    new_page->prev = mru;
    mru = new_page;

    pages_in_memory++;

    return;
}

void lru_remove_page() {
    // Simply pop the head of the linked list
    assert(lru); // To make sure lru is not a null pointer
    lru = lru->next;
    pages_in_memory--;
}

void lru_use_page(struct page *page) {
    // Check if the page is cached or not
    for (struct page *cur = lru; cur; cur = cur->next) {
        if (cur->pageno == page->pageno) {
            // Page is already in the memory, now we need to make it the most recently used
            if (cur->next) cur->next->prev = cur->prev;
            if (cur->prev) cur->prev->next = cur->next;
            cur->prev = mru;
            cur->next = 0;
            mru->next = cur;
            mru = cur;
            return;
        }
    }

    // Page is not in the memory, so either there is space in the memory or we will need to replace the least recently used
    if (pages_in_memory >= MAX_PAGES_IN_MEM) {
        lru_remove_page(); // Remove the least recently used to be replaced by the new page
    }
    lru_add_page(page); // Add the new page
}

/* Now we will implement the FIFO algorithm
 * This time we will simply use a linked queue with the same struct used for LRU
 */

struct page *f1 = 0; // This is the front of the queue (first in)
struct page *l1 = 0; // This is the back of the queue (last in)

void fifo_add_page(struct page *page) {
    assert(page);
    if (!l1) { // Empty queue
        f1 = l1 = page;
        return;
    }

    // Insert the page at the end of the queue
    l1->next = page;
    page->prev = l1;
    l1 = page;

    pages_in_memory++;

    return;
}

void fifo_remove_page() {
    f1 = f1->next;
    pages_in_memory--;
}

void fifo_use_page(struct page *page) {
    // Check if the page is already in the memory
    for (struct page *cur = f1; cur; cur = cur->next) {
        if (cur->pageno == page->pageno) {
            // Page found, no need for replacement
            return;
        }
    }

    // Page not found
    if (pages_in_memory >= MAX_PAGES_IN_MEM) {
        fifo_remove_page(); // If the memory is full, pop the first element
    }
    fifo_add_page(page); // Push the new page
}