#include <db/Database.hpp>

using namespace db;
using namespace std;
BufferPool &Database::getBufferPool() { return bufferPool; }

Database &db::getDatabase() {
  static Database instance;
  return instance;
}

void Database::add(std::unique_ptr<DbFile> file) {
  // TODO pa1: add the file to the catalog. Note that the file must not exist.
  // Get the name from the file
  string name = file->getName();

  // Check if the file already exists in the catalog
  if (catalog.find(name) != catalog.end()) {
    throw runtime_error("File already exists, duplicate name");
  }

  // Add the file to the catalog
  catalog[name] = move(file);
}

std::unique_ptr<DbFile> Database::remove(const std::string &name) {
  // TODO pa1: remove the file from the catalog. Note that the file must exist.
  auto it = catalog.find(name);
  if(it == catalog.end()){
    throw runtime_error("File does not exist");
  }else{
    //flush any dirty page associated with the file
    bufferPool.flushFile(name);
    unique_ptr<DbFile> removedFile = move(it->second);
    //remove file in catalog
    catalog.erase(it);
    return removedFile;
  }
  
}

DbFile &Database::get(const std::string &name) const {
  // TODO pa1: get the file from the catalog. Note that the file must exist.
  //use iterator to find existance of file
  auto it = catalog.find(name);
  //throw error if file DNE
  if(it == catalog.end()){
    throw runtime_error("File does not exist");
  }
  //dereference and return the actual file
  return *(it->second);
}
