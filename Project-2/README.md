Subject 7: Contacts Management
==============================

###Project summary:

Gmail and other email services, or even some smartphones applications extensively use contacts management. Such applications need efficient algorithms to implement features such as **contact search**, **contact insertion** and **contact deletion**.

This project aims to implement some of these features on a list of registers that might contain info like **name**, **phone number**, **email** and **address**.

The search should be dynamic and the application should display the best candidates as the user types each new character. The more characters the user inputs, the closest the search results should be to his/her interest.

There is also a possibility the user might misspell the search keywords. The search algorithm should therefore suggest any corrections that might approach to the most similar registers of the contact list.

The file that contains all the registers is **contacts.txt**.

###Questions:

**Q**: What algorithm will be used to search the contacts list?  
**A**: An approximate string search algorithm will be used.

**Q**: What container should be used to store the contacts during runtime?  
**A**: One of the most appropriate choices would be to use a [set](http://www.cplusplus.com/reference/set/set/). Sets not only store unique elements following a specific order, but are also implemented as *binary search trees*, which will be perfect for the **search**, **insertion** and **deletion** operations we need to implement.

**Q**: How long will a contact insertion/deletion/search operation take?  
**A**: Since the contacts container is a *set*, which (again) are implemented as *binary search trees*, these operations will have a **time complexity** of **O(log n)**.

###Problems to solve:

- [x] File syntax to store contacts persistent data;  
- [x] Search algorithms.

###File syntax:

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
