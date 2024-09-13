#include <db/BufferPool.hpp>
#include <db/Database.hpp>
#include <numeric>

using namespace db;
using namespace std;
const size_t maxPages = DEFAULT_NUM_PAGES;
BufferPool::BufferPool()
// TODO pa1: add initializations if needed
{
  // TODO pa1: additional initialization if needed
}

BufferPool::~BufferPool() {
  // TODO pa1: flush any remaining dirty pages
  for(auto const &entry : Pagetable){
    if(isDirty(entry.first)){
      flushPage(entry.first);
    }
  }
}

Page &BufferPool::getPage(const PageId &pid) {
  // TODO pa1: If already in buffer pool, make it the most recent page and return it
  if(contains(pid)){
    lruList.remove(pid);
    lruList.push_back(pid);
    return Pagetable[pid];
  }
  // TODO pa1: If there are no available pages, evict the least recently used page. If it is dirty, flush it to disk
  if(Pagetable.size() >= DEFAULT_NUM_PAGES){
    PageId lruPage = lruList.front();
    lruList.pop_front();

    if(isDirty(lruPage)){
      flushPage(lruPage);
    }
    Pagetable.erase(lruPage);
    dirtyPages.erase(lruPage);
  }
  // TODO pa1: Read the page from disk to one of the available slots, make it the most recent page
  DbFile &file = db::getDatabase().get(pid.file);
  Page newpage;
  file.readPage(newpage, pid.page);
  Pagetable[pid] = newpage;
  lruList.push_back(pid);
  
  return Pagetable[pid];
  
}

void BufferPool::markDirty(const PageId &pid) {
  // TODO pa1: Mark the page as dirty. Note that the page must already be in the buffer pool
}

bool BufferPool::isDirty(const PageId &pid) const {
  // TODO pa1: Return whether the page is dirty. Note that the page must already be in the buffer pool
}

bool BufferPool::contains(const PageId &pid) const {
  // TODO pa1: Return whether the page is in the buffer pool
}

void BufferPool::discardPage(const PageId &pid) {
  // TODO pa1: Discard the page from the buffer pool. Note that the page must already be in the buffer pool
}

void BufferPool::flushPage(const PageId &pid) {
  // TODO pa1: Flush the page to disk. Note that the page must already be in the buffer pool
}

void BufferPool::flushFile(const std::string &file) {
  // TODO pa1: Flush all pages of the file to disk
}
