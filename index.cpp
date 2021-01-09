#include <iostream>
#include <string>
#include <stdexcept>
/*
the provided source, driver, and header files. 
When testing your code, note that the driver
file reads from "input.html", so you will 
need to rename any test file to input.html before running.
*/
#include "html.h"


using namespace std;
using namespace HTML;

Tag* Tag::makeTag(const string& tag, const unordered_map<string,
 string>& attr, const vector<Contents*>& contents)
{

    if((tag == "style") || (tag == "script") ||
    (tag == "head"))
    {
        return new InvisibleTag(tag, attr, contents );
    }
    else if((tag == "br") || (tag == "hr"))
    {
        return new LineBreak(tag, attr, contents);
    }
    else if(tag == "img")
    {
        return new Image(tag, attr, contents);
    }
    else if((tag == "p") || (tag == "h1") ||
    (tag == "h2") || (tag == "h3") ||
    (tag == "h4") || (tag == "h5") || 
    (tag == "h6") || (tag == "div"))
    {
        return new Paragraph(tag, attr, contents);
    }
    else if(tag == "ul")
    {
        return new UnorderedList(tag, attr, contents);
    }
    else if(tag == "ol")
    {
        return new OrderedList(tag, attr, contents);
    }
    else if(tag == "table")
    {
        return new Table(tag, attr, contents);
    }
    else if(tag == "tr")
    {
        return new TableRow(tag, attr, contents);
    }
    else if((tag == "td") || (tag == "th"))
    {
        return new TableColumn(tag, attr, contents);
    }
    else
    {
        return new Tag(tag, attr, contents);
    }
    
    //getLinkTarget() : { return ""; }
    //Tag::display(...);

    //Tag::display(out, links); for every display function


    //g++ html-driver.cpp html-provided.cpp
    // html-extra.cpp yoursource.cpp
/*
 the "heart" of the program.
 Takes in the Tag type,
attributes, and contents,
and it outputs a pointer
to the appropriate subclass of Tag.
*/
}

string Tag::getLinkTarget() const
{
    string att = "";
    unordered_map<string, string>::const_iterator m = attributes.find("href");

    if((m != attributes.end()) && (m->first == "href"))
    {
    att = m->second;
    return att;
    }

    return att;
    
}

void Paragraph::display(ostream& out, vector<const Tag*>& links) const
{
    out << '\n';
    Tag::display(out, links);
    out << '\n';
}

void Image::display(ostream& out, vector<const Tag*>& links) const
{
    unordered_map<string, string>::const_iterator a = attributes.find("alt");
    
    
    if((a != attributes.end()) && (a->first == "alt"))
    {
    out << a->second;
    }
    else
    {
        out << "(image)";
    }



   if (getLinkTarget() != "")
    links.push_back(this);
  for (Contents* c : contents)
    c->display(out, links);
   
  
}

void UnorderedList::display(ostream& out, vector<const Tag*>& links) const
{
    out << '\n';
    for (Contents* c : contents)
    {
    out << " * ";
    c->display(out, links);
    out << '\n';
    }
}
  

void OrderedList::display(ostream& out, vector<const Tag*>& links) const
{
    int num = 0;
  out << '\n';
  for(Contents* c : contents)
  {
    out << " " << ++num << ". ";
    c->display(out, links);
    out << '\n';
  }

}

