#include "Book.hpp"
#include <iostream>
#include "ArrayBag.hpp"
#include "LibraryRecord.hpp"

int main()
{
  Book book1("moby","joe",254,true);
  Book book2("harry pot","dobby is free elf",254,true);
  
  LibraryRecord lib1;
  lib1.checkIn(book1);
  lib1.checkOut(book1);
  lib1.checkIn(book1);
  lib1.checkOut(book1);
  lib1.checkIn(book1);

 
  LibraryRecord lib2;
  lib2.checkIn(book1);
  lib2.checkOut(book1);
  lib2.checkIn(book1);


  lib1.display(); 
  std::cout << "\n" << "\n";
  lib2.display();
  std::cout << "\n" << "\n";
  lib1 += lib2;
  std::cout<< lib1.getCurrentSize();
  lib1.display();
  
  
  return 0;

}