Subject 7: Contacts Management
==============================

Gmail and other email services, or even smartphones are applications that extensively use contacts management. Such applications need efficient contacts search, insertion and deletion algorithms.

This project aims to implement some of these features on a list of registers that might contain info like **name**, **address**, **e-mail**, **phone number** and **other information**.

The search should be dynamic and the application should display the best candidates as the user types each new character. The more characters the user inputs, the closest the search results should be to his/her interest.

There is also a possibility the user might misspell the search keywords. The search algorithm should therefore suggest any corrections that might approach them to the most similar registers of the contact list.

The file that contains all the registers is **contacts.txt**.

###Questions:

**Q**: yyy?  
**A**: xxx.

**Q**: yyy?  
**A**: cccccc.

###Problems to solve:

1. asdads;
2. adsasd.

###File sintax:

nContacts  
firstName lastName phoneNumber email address  
firstName lastName phoneNumber email address  
firstName lastName phoneNumber email address  
...

#####Legend:

- nContacts: unsigned long
	- number of contacts stored
- firstName: string
	- contact first name
- lastName: string
	- contact last name
- phoneNumber: string
	- contact phone number
- email: string
	- contact e-mail
- address: string
	- contact address
