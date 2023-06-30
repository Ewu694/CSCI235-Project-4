#include <fstream>
#include "Manual.hpp"


/**
  Default constructor.
  Default-initializes all private members. 
  Booleans are default-initialized to False
*/
Manual::Manual(): has_website_{false}, has_visual_aid_{false}, website_{""}, device_{""}
{	
}

/**
  Parameterized constructor.
  @param     : The title of the book (a string)
  @param     : The author of the book (a string)
  @param     : The number of pages in the book (a positive integer)
  @param     : A flag indicating whether the book is in digital form 
                with DEFAULT VALUE False (a Boolean)
  @param     : The name of the device (a string)
  @param     : The URL that is in the format 
                'https://www.something.something' 
                or 'http://www.something.something' 
                with the last 'something' being at least 2 characters 
                with DEFAULT VALUE empty string (a string)
  @param     : A Boolean indicating the presence of a visual aid 
                with DEFAULT VALUE False
  @post      : The private members are set to the values of the 
                corresponding parameters. 
                If a URL is provided, the website flag is set to True.
                If the URL is ill-formatted, the website is set to 
                empty string and the website flag is set to False.
*/
Manual::Manual(std::string name, std::string author, int page_count, std::string model, bool is_digital, std::string url, bool aid) : Book(name, author, page_count, is_digital), has_visual_aid_{aid}, device_{model}
{
  const std::regex pattern("((http|https)://)(www.)[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
  
  // If website in invalid, set website_ to empty string and set has_website_ to false
  // ** Differs from setWebsite instructions
  if (regex_match(url,pattern)) {
    website_ = url;
    has_website_ = true;
  }
  else if(url == "NONE")
  {
    website_ = "NONE";
    has_website_ = false;
  }
  else if((url.size() > 0) && !regex_match(url,pattern))//if there is a website param that has input, does not match the pattern properly and is not none, then set website_ to
  {
    website_ = "Broken Link";
    has_website_ = true;
  }
  else {
    website_ = ""; 
    has_website_ = false;
  }
  std::size_t found = device_.find('-'); //finds the hyphen in the device 
  device_ = device_.substr(0, found);//after that, set the device to just be the what type of device it is by doing 0 - where the hyphen is found
}

/**
  @return  : the variable indicating the device the manual is for
**/
std::string Manual::getDevice() const
{
  return device_;
}

/**
  @return  : the url for the website
**/
std::string Manual::getWebsite() const
{
  return website_;
}

/**
  @return  : the visual aid flag
**/
bool Manual::hasVisualAid() const
{
  return has_visual_aid_;
}

/**
  @return  : the has website flag
**/
bool Manual::hasWebsite() const
{
  return has_website_;
}

/**
  @param   : a reference to a website link (string) that is in the format 
             'https://www.something.something' 
             or 'http://www.something.something' 
             with the last 'something' being at least 2 characters
  @return  : has_website_ flag (a boolean)
  @post    : If the link is not correctly formatted, 
             store "Broken Link" in the link member variable (see <regex>) 
             and either way set the has website flag to True
**/
// (** Differs from parameterized constructor)
bool Manual::setWebsite(const std::string& site)
{
  const std::regex pattern("((http|https)://)(www.)[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
  
  if (regex_match(site,pattern)) {
    website_ = site;
  }
  else {
    website_ = "Broken Link";
  }

  has_website_ = true;

  return has_website_;
} 

/**
  @param  : a reference to a string representing the device
  @post   : sets the private member variable to the value of the parameter
**/
void Manual::setDevice(const std::string& model)
{
  device_ = model;
}

/**
  @param  : a boolean
  @post   : sets the private member variable indicating the presence 
            of a visual aid to the value of the parameter
**/
void Manual::setVisualAid(const bool& aid)
{
  has_visual_aid_ = aid;
}

void Manual::display()
{
  std::string digital_true_false = "";//used later in the string sentence
  if(isDigital() == true)
  {
    digital_true_false = "It is ";//If the book is digital, empty string gets set to "It is"
  }
  else
  {
    digital_true_false = "It is not ";//If not, it is set to "It is not"
  }
  std::string has_website = "";//used later to hold a different value depending on if true/false
  if(hasWebsite())
  {
    has_website = website_;
  }
  else 
  {
    has_website = " NONE ";
  }
  int found = device_.find('-');
  std::string device_model;
  device_model = device_.substr(0, found);
  std::cout <<  getTitle() << " is written by " << getAuthor() << " company for device: " << device_model << ". " << "Website: " << website_  << ". Page Count: " << getPageCount() << ". " << digital_true_false << "available digitally.\n";
}

void Manual::displayFilter(const std::string &key)
{
   if(device_ == key)
      display();
}
