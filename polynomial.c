#include <stdio.h>
#include <stdlib.h>

// Structure to represent a term in the polynomial
typedef struct Term {
    int coefficient;
    int exponent;
    struct Term* next;
} Term;

// Function to create a new term with given coefficient and exponent
Term* createTerm(int coefficient, int exponent) {
    Term* term = (Term*)malloc(sizeof(Term));
    term->coefficient = coefficient;
    term->exponent = exponent;
    term->next = NULL;
    return term;
}

// Function to insert a term into the polynomial
void insertTerm(Term** poly, int coefficient, int exponent) {
    Term* newTerm = createTerm(coefficient, exponent);
    if (*poly == NULL) {
        *poly = newTerm;
    } else {
        Term* curr = *poly;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newTerm;
    }
}

// Function to display the polynomial
void displayPolynomial(Term* poly) {
    if (poly == NULL) {
        printf("Polynomial is empty.\n");
        return;
    }

    while (poly != NULL) {
        printf("%dx^%d ", poly->coefficient, poly->exponent);
        poly = poly->next;
        if (poly != NULL) {
            printf("+ ");
        }
    }
    printf("\n");
}

// Function to add two polynomials
Term* addPolynomials(Term* poly1, Term* poly2) {
    Term* result = NULL;
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent > poly2->exponent) {
            insertTerm(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            insertTerm(&result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else {
            int sum = poly1->coefficient + poly2->coefficient;
            if (sum != 0) {
                insertTerm(&result, sum, poly1->exponent);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        insertTerm(&result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        insertTerm(&result, poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
    }

    return result;
}

// Function to multiply two polynomials
Term* multiplyPolynomials(Term* poly1, Term* poly2) {
    Term* result = NULL;
    Term* temp = poly2;

    while (poly1 != NULL) {
        while (temp != NULL) {
            int coefficient = poly1->coefficient * temp->coefficient;
            int exponent = poly1->exponent + temp->exponent;
            insertTerm(&result, coefficient, exponent);
            temp = temp->next;
        }
        temp = poly2;
        poly1 = poly1->next;
    }

    return result;
}

// Function to subtract two polynomials
Term* subtractPolynomials(Term* poly1, Term* poly2) {
    Term* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent > poly2->exponent) {
            insertTerm(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            insertTerm(&result, -poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else {
            int difference = poly1->coefficient - poly2->coefficient;
            if (difference != 0) {
                insertTerm(&result, difference, poly1->exponent);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        insertTerm(&result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        insertTerm(&result, -poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
    }

    return result;
}

int main() {
    int choice;
    Term* polynomial1 = NULL;
    Term* polynomial2 = NULL;
    Term* result = NULL;

    do {
        printf("Polynomial Operations:\n");
        printf("1. Input Polynomial 1\n");
        printf("2. Input Polynomial 2\n");
        printf("3. Add Polynomials\n");
        printf("4. Multiply Polynomials\n");
        printf("5. Subtract Polynomials\n");
        printf("6. Display Polynomials\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int numTerms;
                printf("Enter the number of terms in Polynomial 1: ");
                scanf("%d", &numTerms);

                for (int i = 0; i < numTerms; i++) {
                    int coefficient, exponent;
                    printf("Enter the coefficient and exponent of term %d: ", i + 1);
                    scanf("%d %d", &coefficient, &exponent);
                    insertTerm(&polynomial1, coefficient, exponent);
                }
                break;
            }
            case 2: {
                int numTerms;
                printf("Enter the number of terms in Polynomial 2: ");
                scanf("%d", &numTerms);

                for (int i = 0; i < numTerms; i++) {
                    int coefficient, exponent;
                    printf("Enter the coefficient and exponent of term %d: ", i + 1);
                    scanf("%d %d", &coefficient, &exponent);
                    insertTerm(&polynomial2, coefficient, exponent);
                }
                break;
            }
            case 3: {
                result = addPolynomials(polynomial1, polynomial2);
                printf("Polynomials added successfully.\n");
                break;
            }
            case 4: {
                result = multiplyPolynomials(polynomial1, polynomial2);
                printf("Polynomials multiplied successfully.\n");
                break;
            }
            case 5: {
                result = subtractPolynomials(polynomial1, polynomial2);
                printf("Polynomials subtracted successfully.\n");
                break;
            }
            case 6: {
                printf("Polynomial 1: ");
                displayPolynomial(polynomial1);
                printf("Polynomial 2: ");
                displayPolynomial(polynomial2);
                printf("Result: ");
                displayPolynomial(result);
                break;
            }
            case 7: {
                printf("Exiting...\n");
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\n");

    } while (choice != 7);

    return 0;
}
