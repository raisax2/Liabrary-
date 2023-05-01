#include "LibraryRecord.hpp"

LibraryRecord::LibraryRecord()
{
    record = {};
}

/** @param:   A reference to a Book object to be checked in
    @return:  returns true if a book was successfully added to items_, false otherwise
    @post:    adds book to items_.
 **/
bool LibraryRecord::checkIn(const Book &obj)
{
    return add(obj);
    /*if (item_count_<DEFAULT_CAPACITY) {
        item_count_ = obj;
        obj++;
    }*/
}

/** @param:   A reference to a Book object to be checked out
    @return:  returns true if a book was successfully removed from items_, false otherwise
    @post:    removes the book from the LibraryRecord and if remove was successful, it adds the book to the vector of checked-out.
 **/
bool LibraryRecord::checkOut(const Book &obj)
{
    if (remove(obj) == true)
    {
        record.push_back(obj);
        return true;
    }
    else
        return false;
}

/**
  @param:   A reference to a Book object
  @return:  The number of times (int) the referenced Book has been checked out
*/
int LibraryRecord::getCheckOutHistory(const Book &obj) const
{
    int count = 0;
    for (int i = 0; i < record.size(); i++)
        if(record[i]==obj)
            count ++;
    return count;
}

/**
    @post:    Outputs the names of the Books in the LibraryRecord and the number of times each Book has been cheked out

      For each Book in the LibraryRecord you will output:
             "[title_] is written by [author_]. Page Count: [page_count_]. [It is / It is not] available digitally.\n
             It has been checked out [_] times."
  **/
void LibraryRecord::display()
{
    for (int i = 0; i < item_count_; i++)
    {
        std::cout << items_[i].getTitle() << " is written by " << items_[i].getAuthor() << ". Page Count: " << items_[i].getPageCount() << ".";
        if (items_[i].isDigital() == true)
            std::cout << "It is available digitally.\n";
        else
            std::cout << "It is not available digitally.\n";
        std::cout << "It has been checked out " << getCheckOutHistory(items_[i]) << " times.\n";
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
        std::cout << items_[i].getTitle();
        if (i== item_count_-1)
            std::cout << "!";
        else
            std::cout << ", ";
    }
}

/**
  @return:    Returns true if the LibraryRecord was successfully duplicated, false otherwise (there is nothing to duplicate or duplicating would exceed DEFAULT_CAPACITY).
  @post:      Duplicates all the items in the LibraryRecord
  Example: we originally have [book1, book2] and after duplication we have [book1, book2, book1, book2]
*/
bool LibraryRecord::duplicateStock()
{
    if (item_count_ > DEFAULT_CAPACITY || 2*item_count_ >  DEFAULT_CAPACITY)
    {
        return false;
    }
    int  c= item_count_;
    for (int i = 0; i < c; i++ )
        add(items_[i]);
    return true;
}

/**
  @param:   A reference to a book
  @return: True if at least one copy of the referenced book was removed from items_, false otherwise
  @post: remove all occurrences of the referenced book
*/
bool LibraryRecord::removeStock(const Book &obj)
{
    if(item_count_>0)
    {
        int c= item_count_;
        for (int i = 0; i < c; i++)
            remove(obj);
        return true;
    }
    return false;
}

/**
  @param:   A reference to another LibraryRecord
  @return:  Returns true if the 2 library records have the same contents, regardless of their order. For example, if the current holdings of the LibraryRecord are [book1, book2, book3]
  and those of the referenced LibraryRecord are [book3, book1, book2], it will return true
*/
bool LibraryRecord::equivalentRecords(const LibraryRecord &lib)
{
    if(item_count_==lib.getCurrentSize())
    {
        for (int i=0; i < item_count_; i++)
        {
            if(getFrequencyOf(items_[i])==lib.getFrequencyOf(items_[i]))
                return true;
        }
    }
    return false;
}

/**
    @param:   A reference to another LibraryRecord object
    @post:    Combines the contents from both LibraryRecord objects, including duplicates.
    Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]

    IMPORTANT: We are carrying over the number of times a book has been checked out. For example, if we have LibraryRecord1 += LibraryRecord2 and
    book4 is in LibraryRecord2 and has been checked out 2 times, then it should still be checked out 2 times in LibraryRecord1 after the += operation
    Hint: use getCheckOutHistory and the checkout history vector
*/
void LibraryRecord::operator+=(const LibraryRecord &lib)
{
    if((item_count_+lib.getCurrentSize())< DEFAULT_CAPACITY)
    {
        for (int i = 0; i < lib.getCurrentSize(); i++)
        {
            add(lib.items_[i]);
            for (int j=0; j < lib.getCheckOutHistory(lib.items_[i]); j++)
                record.push_back(lib.items_[i]);
        }

    }
}

/** @param:   A reference to another LibraryRecord object
    @post:    Combines the contents from both LibraryRecord objects, EXCLUDING duplicates.
    Example: [book1, book2, book3] /= [book1, book4] will produce [book1, book2, book3, book4]

    IMPORTANT: We are carrying over the nunber of times a book has been checked out. For example, if we have LibraryRecord1 /= LibraryRecord2 and
    book4 is in LibraryRecord2 and has been checked out 2 times, then it should still be checked out 2 times in LibraryRecord1 after the /= operation
    Hint: use getCheckOutHistory and the checkout history vector
*/
void LibraryRecord::operator/=(const LibraryRecord &lib)
{
    if ((item_count_+(lib.getCurrentSize()))<DEFAULT_CAPACITY)
    {
        for(int i=0;i<lib.getCurrentSize();i++)
        {
            if(getFrequencyOf(lib.items_[i])==0){
                add(lib.items_[i]);
                for(int j =0; j<lib.getCheckOutHistory(lib.items_[i]); j++) {
                    record.push_back(lib.items_[i]);
            }
        }
            
        }
    }
}
