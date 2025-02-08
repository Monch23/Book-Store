#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <limits>

using namespace std;

typedef struct {
	char title[100];
	char author[100];
	char isbn[20];
	bool available;
} Book;

const size_t books_count = 100;
int idx = 0;

bool is_have_in_store(const Book *store, const char *title, const char *author, const char *isbn) {
	for (int i = 0; i < idx; ++i) {
		if (strcmp(store[i].title, title) == 0) {
			cout << "Book with title " << "'" << title << "'" << " has in store" << endl;
			return true;
		}
		if (strcmp(store[i].author, author) == 0) {
		    cout << "Book with author " << "'" << author << "'" << " has in store" << endl;
		    return true;
		}
		if (strcmp(store[i].isbn, isbn) == 0) {
		    cout << "Book with ISBN " << "'" << isbn << "'" << " has in store" << endl;
		    return true;
		}
	}
	
	return false;

}

void add_book(Book *store) {
    
    if (idx == books_count) {
        cout << "Book store is full" << endl;
        return;
    }
    
    char tmp_title[100] = {0};
    char tmp_author[100] = {0};
    char tmp_isbn[20] = {0};
    
    cin.ignore();
    cout << "Title: ";
    cin.getline(tmp_title, sizeof(tmp_title));
    cout << "Author: ";
    cin.getline(tmp_author, sizeof(tmp_author));
    cout << "ISBN: ";
    cin.getline(tmp_isbn, sizeof(tmp_isbn));

    if (is_have_in_store(store, tmp_title, tmp_author, tmp_isbn) == true) {
        return;
    }
    
    strcpy(store[idx].title, tmp_title);
    strcpy(store[idx].author, tmp_author);
    strcpy(store[idx].isbn, tmp_isbn);
    store[idx].available = true;
    ++idx;
    
    return;
}

void show_all_books(Book *store) {
    if (store == NULL) {
        return;
    }
    
    for (int i = 0; i < idx; ++i) {
        cout << "Title: " << store[i].title << endl;
        cout << "Author: " << store[i].author << endl;
        cout << "ISBN: " << store[i].isbn << endl;
        cout << "Available: " << (store[i].available == true ? "Yes" : "No") << endl << endl;
    }
    
    return;
}

void search_by_author_or_title(Book *store) {
    if (store == NULL) {
        return;
    }
    
    char tmp[100] = {0};
    
    cout << "Input title or author: " << endl;
    cin.ignore();
    cin.getline(tmp, sizeof(tmp));
    
    for (int i = 0; i < idx; ++i) {
        if (!strncmp(tmp, store[i].title, strlen(tmp)) || !strncmp(tmp, store[i].author, strlen(tmp))) {
            cout << endl << "Title: " << store[i].title << endl;
            cout << "Author: " << store[i].author << endl;
            cout << "ISBN: " << store[i].isbn << endl;
            cout << "Available: " << (store[i].available == true ? "Yes" : "No") << endl << endl;
        }
    }
    
    return;
}

void book_borrow(Book *store) {
    if (store == NULL) {
        return;
    }
    
    char tmp_isbn[20] = {0};
    
    cout << "Input book's isbn: " << endl;
    cin.ignore();
    cin.getline(tmp_isbn, sizeof(tmp_isbn));
    
    for (int i = 0; i < idx; ++i) {
        if ((strcmp(tmp_isbn, store[i].isbn) == 0) && (store[i].available == true)) {
            cout << "You are borrowed a book with title " << "'" << store[i].title << "'" << endl;
            store[i].available = false;
            return;
        }    
    }
    
    cout << "Invalid ISBN or book are borrowed" << endl;
    return;
}

void return_book(Book *store) {
    if (store == NULL) {
        return;
    }
    
    char tmp_isbn[20] = {0};
    
    cout << "Input borrowed book's isbn: " << endl;
    cin.ignore();
    cin.getline(tmp_isbn, sizeof(tmp_isbn));
    
    for (int i = 0; i < idx; ++i) {
        if ((strcmp(tmp_isbn, store[i].isbn) == 0) && (store[i].available == false)) {
            cout << "You are returned borrowed book with title " << "'" << store[i].title << "'" << endl;
            store[i].available = true;
            return;
        }
    }
    
    cout << "Invalid ISBN or book are returned" << endl;
    return;
}

int main() {
	Book *books = (Book*)calloc(books_count, sizeof(Book));
    size_t choose = 0;
    size_t add = 1;
    size_t list_books = 2;
    size_t search = 3;
    size_t borrow = 4;
    size_t ret_book = 5;
    size_t term = 6;
    
    cout << "Book Store Is Opened !" << endl << endl;
    while (choose != term) {
        cout << "1) Add Book" << endl;
        cout << "2) List Books" << endl;
        cout << "3) Search Book" << endl;
        cout << "4) Borrow Book" << endl;
        cout << "5) Return Borrowed Book" << endl;
        cout << "6) Exit" << endl;
        cin >> choose;
        
        if (choose == add) {
            add_book(books);
        } else if (choose == list_books) {
            show_all_books(books);
        } else if (choose == search) {
            search_by_author_or_title(books);
        } else if (choose == borrow) {
            book_borrow(books);
        } else if (choose == ret_book) {
            return_book(books); 
        } else if (choose == term) {
            break;
        } else {
            cout << "Invalid Action" << endl;
        }
    }
    
    cout << endl << "Book Store Is Closed !" << endl;
    free(books);
	return 0;
}





