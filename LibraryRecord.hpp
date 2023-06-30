#ifndef LIBRARY_RECORD_
#define LIBRARY_RECORD_

#include "ArrayBag.hpp"
#include "Book.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Textbook.hpp"
#include "Novel.hpp"
#include "Manual.hpp"
#include <regex>

class LibraryRecord : public ArrayBag<Book*>{
  public:
    LibraryRecord(); //default constructor

    /** @param:   A reference to a Book object to be checked in
      @return:  returns true if a book was successfully added to items, false otherwise
      @post:    adds book to items.
    **/
    LibraryRecord(const std::string file_name);

	  bool checkIn(Book *new_entry);
    
    /** @param:   A reference to a Book object to be checked out   
        @return:  returns true if a book was successfully removed from items_, false otherwise
        @post:    removes the book from the LibraryRecord and if remove was successful, it adds the book to the check_out_history_ vector.
    **/
	  bool checkOut(Book *an_entry);

    /**
      @param:   A reference to a Book object
      @return:  The number of times (int) the referenced Book has been checked out
    */
    int getCheckOutHistory(Book *an_entry);

    /**
      @return item_count_ : the current size of the bag
    **/

    
    std::vector<Book*> toVector();

    /**
    @post:    Outputs the names of the Books in the LibraryRecord and the number of times each Book has been checked out

        For each Book in the LibraryRecord you will output:
        [title_] is written by [author_]. Page Count: [page_count_]. [it is / is not] available digitally.\n
        It has been checked out [_] times.
    **/
    void display();

    /**
      @post:    Prints the title of each Book in the LibraryRecord
      Example:
      "title1, title2, title3, title4!" Note the commas and exclamation mark.
    */  
    void displayTitles();

    /**
      @return:    Returns true if the LibraryRecord was successfully duplicated, false otherwise (there is nothing to duplicate or duplicating would exceed DEFAULT_CAPACITY).
      @post:      Duplicates all the items in the LibraryRecord
      Example: we originally have [book1, book2] and after duplication we have [book1, book2, book1, book2]
    */
    bool duplicateStock();

    /**
      @param:   A reference to a book
      @return: True or false depending on whether or not an item was removed
      @post: remove all elements of that book
    */
    bool removeStock(Book *an_entry);

    /**
      @param:   A reference to another LibraryRecord
      @return:  Returns true if the 2 library records have the contents, regardless of their order. For example, if the current holdings of the LibraryRecord are [book1, book2, book3]
      and those of the referenced LibraryRecord are [book3, book1, book2], it will return true
    */
    bool equivalentRecords(LibraryRecord& a_library_record);

    /** @param:   A reference to another ArrayBag object
      @post:    Combines the contents from both ArrayBag objects, EXCLUDING duplicates.
      Example: [book1, book2, book3] /= [book1, book4] will produce [book1, book2, book3, book4]

      IMPORTANT: We are carrying over the amount of times a book has been checked out.
      If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
      Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
    void operator/=(LibraryRecord& a_library_record);

    /**
        @param:   A reference to another LibraryRecord object
        @post:    Combines the contents from both LibraryRecord objects, including duplicates.
        Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]

        IMPORTANT: We are carrying over the amount of times a book has been checked out.
        If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
        Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
    void operator+=(LibraryRecord& a_library_record);

    void displayFilter(const std::string &key);//if information matches key, then display
    
  protected:
   
    std::vector<Book*> check_out_history_; //a list of all the items that have been checked out

 
};
#endif
