#include "LibraryRecord.hpp"


/** default constructor**/
LibraryRecord::LibraryRecord() : ArrayBag<Book*>()
{
}

/** parameterized constructor*/

LibraryRecord::LibraryRecord(const std::string file_name)
{
  std::ifstream book_data (file_name, std::ifstream::in);

  std::string line;//used to store the first line of code
  std::string title;//used to store title param
  std::string author;//used to store author param
  std::string page_count_str;//used to store page count param
  int page_count;//used later to store the int value of page_count 
  std::string digital_str;//used to store the digital bool
  bool is_digital;//used later to store the bool value of is_digital
  std::string genre;//used to store the genre 
  std::string subject;//used to store the book subject
  std::string grade_level_str;//used to store the grade level of book
  grade_level book_grade_level;//used later to store the grade_level of grade_level1
  std::string film_adaptation_str;///used to store film adaptation param bool
  bool film_adaptation;//used later to store the bool value of film adaptation
  std::string review_questions_str;//used to store review_questions bool
  bool review_questions;//used to store the review_question bool
  std::string device_model;//used to store device model
  std::string website;//used to store website
  std::string book_type;//used to store the book type, where 1 == novel, 2 == textbook, and 3 == manual
  getline(book_data, line);//gets first line of the dataset
  while(!book_data.eof()) 
  {
   getline(book_data, title, ',');//next few getlines are used to store the title, author and page count
   getline(book_data, author,',');
   getline(book_data, page_count_str, ',');
   std::stringstream int_page_count;
   int_page_count << page_count_str;
   int_page_count >> page_count;
   getline(book_data, digital_str, ',');
   std::stringstream bool_is_digital;
   bool_is_digital << digital_str;
   bool_is_digital >> is_digital;
   getline(book_data, genre, ',');
   getline(book_data, subject, ',');
   getline(book_data, grade_level_str, ',');
   if(grade_level_str == "NONE")
   {
    book_grade_level = NONE;
   }
   else if(grade_level_str == "ELEMENTARY")
   {
    book_grade_level = ELEMENTARY;
   }
   else if(grade_level_str == "JUNIOR HIGH")
   {
    book_grade_level = JUNIOR_HIGH;
   }
   else if(grade_level_str == "HIGH SCHOOL")
   {
    book_grade_level = HIGH_SCHOOL;
   }
   else
   {
    book_grade_level = COLLEGE;
   }
   getline(book_data, film_adaptation_str, ',');
   std::stringstream bool_film_adaptation;
   bool_film_adaptation << film_adaptation_str;
   bool_film_adaptation >> film_adaptation;
   getline(book_data, review_questions_str, ',');
   std::stringstream bool_review_questions;
   bool_review_questions << review_questions_str;
   bool_review_questions >> review_questions;
   getline(book_data, device_model, ',');
   getline(book_data, website, ',');
   getline(book_data, book_type);
    if(book_type == "1")
    {
      Book* novel1 = new Novel(title, author, page_count, genre, is_digital, film_adaptation);
      checkIn(novel1);
    }
    else if(book_type == "2")
    {
      Book* textbook1 = new Textbook(title, author, page_count, subject, is_digital, book_grade_level, review_questions);
      checkIn(textbook1);
    }
    else
    {
      if(website == "NONE" || "")
      {
        Book* manual1 = new Manual(title, author, page_count, device_model, is_digital, website);
        checkIn(manual1);
      }
      else
      {
        Manual* manual2 = new Manual(title,author, page_count, device_model, is_digital, website);
        manual2 -> setWebsite(website);
        Book* final_manual = manual2;
        checkIn(final_manual);
      }
    }
  }
}
/** @param:   A reference to a Book object to be che,cked in
    @return:  returns true if a book was successfully added to items, false otherwise
    @post:    adds book to items.
 **/
bool LibraryRecord::checkIn(Book *new_entry)
{
  bool has_room = (item_count_ < DEFAULT_CAPACITY);
  if (has_room)
  {
    items_[item_count_] = new_entry;
    item_count_++;
    return true;
  } // end if

  return false;
}

/** @param:   A reference to a Book object to be checked out   
    @return:  returns true if a book was successfully removed from items_, false otherwise
    @post:    removes the book from the LibraryRecord and if remove was successful, it adds the book to the check_out_history_ vector.
 **/
bool LibraryRecord::checkOut(Book *an_entry)
{
  int found_index = getIndexOf(an_entry);
  bool can_remove = !isEmpty() && (found_index > -1);
  if (can_remove)
  {
    item_count_--;
    items_[found_index] = items_[item_count_];
    check_out_history_.push_back(an_entry);
  }

  return can_remove;
}

/**
    @post:    Outputs the names of the Books in the LibraryRecord and the number of times each Book has been checked out
      For each Book in the LibraryRecord you will output:
             [title_] is written by [author_]. Page Count: [page_count_]. [it is / is not] available digitally.\n
             It has been checked out [_] times.
**/
void LibraryRecord::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    int count = getCheckOutHistory(items_[i]);
    items_[i] -> display();
    std::cout << "It has been checked out " << count << " times." << std::endl;
  }
}

/**
  @post:    Prints the title of each Book in the LibraryRecord
  Example:
  "title1, title2, title3, title4!" Note the commas and exclamation mark.
*/
void LibraryRecord::displayTitles()
{
  for (int i = 0; i < item_count_; i++)
  {
    if (i < item_count_ - 1)
    {
      std::cout << items_[i] -> getTitle() << ", ";
    }
    else
    {
      std::cout << items_[i] -> getTitle() << "!\n";
    }
  }
}

/**
  @param:   A reference to a Book object
  @return:  The number of times (int) the referenced Book has been checked out
*/
int LibraryRecord::getCheckOutHistory(Book* an_entry)
{
  int count = 0;

  for (std::size_t j = 0; j < check_out_history_.size(); j++)
  {
    if (check_out_history_[j] == an_entry)
    {
      count++;
    }
  }
  return count;
}



/** @param:   A reference to another ArrayBag object
      @post:    Combines the contents from both ArrayBag objects, EXCLUDING duplicates.
      Example: [book1, book2, book3] /= [book1, book4] will produce [book1, book2, book3, book4]
      IMPORTANT: We are carrying over the amount of times a book has been checked out.
      If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
      Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
void LibraryRecord::operator/=(LibraryRecord& a_library_record)
{
  int index = 0;
  int itemsToAdd = a_library_record.item_count_;
  while (itemsToAdd > 0)
  {
    if (this->item_count_ == DEFAULT_CAPACITY)
    {
      break;
    }
    if (contains(a_library_record.items_[index]))
    {
      break;
    }
    this->checkIn(a_library_record.items_[index]);
    int counter = a_library_record.getCheckOutHistory(a_library_record.items_[index]);
    for (int i = 0; i < counter; i++)
    {
      check_out_history_.push_back(a_library_record.items_[index]);
    }
    index++;
    itemsToAdd--;
  }
}




 /**
        @param:   A reference to another LibraryRecord object
        @post:    Combines the contents from both LibraryRecord objects, including duplicates.
        Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]
        IMPORTANT: We are carrying over the amount of times a book has been checked out.
        If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
        Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
void LibraryRecord::operator+=(LibraryRecord& a_library_record)
{
  int index = 0;
  int itemsToAdd = a_library_record.item_count_;
  while (itemsToAdd > 0)
  {
    if (this->item_count_ == DEFAULT_CAPACITY)
    {
      break;
    }
    this->checkIn(a_library_record.items_[index]);
    int counter = a_library_record.getCheckOutHistory(a_library_record.items_[index]);
    for (int i = 0; i < counter; i++)
    {
      check_out_history_.push_back(a_library_record.items_[index]);
    }
    index++;
    itemsToAdd--;
  }
}


 /**
        @param:   A reference to another LibraryRecord object
        @post:    Combines the contents from both LibraryRecord objects, including duplicates.
        Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]
        IMPORTANT: We are carrying over the amount of times a book has been checked out.
        If book4 is in LibraryRecord2 and has been checked out 2 times then it should still be checked out 2 times in LibraryRecord2
        Hint: use getCheckOutHistory and your checkOutHistory_ vector
    */
std::vector<Book*> LibraryRecord::toVector()
{
  std::vector<Book*> bag_contents;
  for (int i = 0; i < item_count_; i++)
    bag_contents.push_back(items_[i]);

  return bag_contents;
}

/**
  @return:    Returns true if the LibraryRecord was successfully duplicated, false otherwise (there is nothing to duplicate or duplicating would exceed DEFAULT_CAPACITY).
  @post:      Duplicates all the items in the LibraryRecord
  Example: we originally have [book1, book2] and after duplication we have [book1, book2, book1, book2]
*/
bool LibraryRecord::duplicateStock()
{
  if (item_count_ * 2 > DEFAULT_CAPACITY)
  {
    return false;
  }

  for (int i = 0; i < item_count_; i++)
  {
    items_[i + item_count_] = items_[i];
  }
  item_count_ = item_count_ * 2;
  return true;
}

/**
  @param:   A reference to a book
  @return: True or false depending on whether or not an item was removed
  @post: remove all elements of that book
*/
bool LibraryRecord::removeStock(Book* an_entry)
{
  bool res = false;
  while (contains(an_entry))
  {
    int found_index = getIndexOf(an_entry);
    item_count_--;
    for (int i = found_index; i < item_count_; i++)
    {
      items_[i] = items_[i + 1];
    }
    res = true;
  }
  return res;
}

/**
  @param:   A reference to another LibraryRecord
  @return:  Returns true if the 2 library records have the contents, regardless of their order. 
            For example, if the current holdings of the LibraryRecord are [book1, book2, book3]
            and those of the referenced LibraryRecord are [book3, book1, book2], it will return true
*/
bool LibraryRecord::equivalentRecords(LibraryRecord& a_library_record)
{
  bool result = true;

  //copy contents to count duplicates by marking them as empty
  // use copy because should not modify items_
  std::vector<Book*> library_copy = toVector();
  std::vector<Book*> other_copy = a_library_record.toVector();
  Book* empty;

  for (std::size_t i = 0; i < library_copy.size(); i++)
  {
    for (std::size_t j = 0; j < other_copy.size(); j++)
    {
      if (other_copy[j] != empty && other_copy[j] == library_copy[i])
      {
        library_copy[i] = empty;
        other_copy[j] = empty;
      }
    }
  }
  //check that all entries have been accounted for
  // i.e. there are no non-empty left
  for (int i = 0; i < item_count_; i++)
  {
    if (library_copy[i] != empty)
    {
      result = false;
    }
  }
  //check that all entries have been accounted for
  // i.e. there are no non-empty left
  for (int i = 0; i < a_library_record.item_count_; i++)
  {
    if (other_copy[i] != empty)
    {
      result = false;
    }
  }
  return result;
}

void LibraryRecord::displayFilter(const std::string &key)
{
  for(int i = 0; i < item_count_; i++)
  {
    items_[i] -> displayFilter(key);
  }
}
