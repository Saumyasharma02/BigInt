#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int data;
    int carry;
    struct node* next;
    struct node* prev;
};

struct BigInteger {
    struct node* head;
    int length;
};

void freeBigInteger(struct BigInteger a) {
    struct node* current = a.head;
    struct node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    a.head = NULL;
}

int len(struct BigInteger a) {
    int i = 0;
    struct node* temp = a.head;
    while (temp) {
        i++;
        temp = temp->next;
    }
    a.length = i;
    return i;
}

int compare(struct BigInteger a, struct BigInteger b) {
    struct node* tempA = a.head;
    struct node* tempB = b.head;

    while (tempA && tempA->data == 0) tempA = tempA->next;
    while (tempB && tempB->data == 0) tempB = tempB->next;

    if (len(a) < len(b)) return 0;
    if (len(a) > len(b)) return 1;

    while (tempA != NULL && tempB != NULL) {
        if (tempA->data < tempB->data) return 0;
        if (tempA->data > tempB->data) return 1;
        tempA = tempA->next;
        tempB = tempB->next;
    }

    return -1;
}

struct BigInteger initialize(const char *s) {
    struct BigInteger a;
    struct node *tail = NULL;
    a.head = NULL;
    int i;

    for (i = 0; s[i] != '\0' && s[i] != '\n'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            struct node* newNode = (struct node*)malloc(sizeof(struct node));
            newNode->data = s[i] - '0';
            newNode->carry = 0;
            newNode->next = NULL;
            newNode->prev = NULL;
            if (a.head == NULL) {
                a.head = tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }
    a.length = i;
    return a;
}

struct node* reverse(struct node* c) {
    struct node* pre = NULL;
    struct node* temp = NULL;
    while (c) {
        temp = c->next;
        c->next = pre;
        c->prev = temp;
        pre = c;
        c = temp;
    }
    return pre;
}

void display(struct BigInteger a) {
    struct node* temp = a.head;
    while (temp) {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    struct BigInteger c;
    c.head = NULL;
    struct node *t = NULL, *nn = NULL;

    struct node *tempA = a.head;
    struct node *tempB = b.head;

    while (tempA && tempA->next) tempA = tempA->next;
    while (tempB && tempB->next) tempB = tempB->next;

    while (tempA != NULL || tempB != NULL) {
        nn = (struct node*)malloc(sizeof(struct node));
        nn->next = NULL;
        nn->prev = NULL;

        int aData = tempA ? tempA->data : 0;
        int bData = tempB ? tempB->data : 0;
        int carry = t ? t->carry : 0;

        nn->data = (aData + bData + carry) % 10;
        nn->carry = (aData + bData + carry) / 10;

        if (c.head == NULL) {
            c.head = t = nn;
        } else {
            t->next = nn;
            nn->prev = t;
            t = nn;
        }

        if (tempA) tempA = tempA->prev;
        if (tempB) tempB = tempB->prev;
    }

    if (t->carry != 0) {
        nn = (struct node*)malloc(sizeof(struct node));
        nn->data = t->carry;
        nn->carry = 0;
        t->next = nn;
        nn->prev = t;
        nn->next = NULL;
    }

    c.head = reverse(c.head);
    return c;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b) {
    struct BigInteger c;
    c.head = NULL;

    if (compare(a, b) == 0) {
        return c;
    }

    struct node *t = NULL, *nn = NULL;
    struct node *tempA = a.head;
    struct node *tempB = b.head;

    while (tempA && tempA->next) tempA = tempA->next;
    while (tempB && tempB->next) tempB = tempB->next;

    while (tempA != NULL || tempB != NULL) {
        nn = (struct node *)malloc(sizeof(struct node));
        nn->next = NULL;
        nn->prev = NULL;

        int aData = tempA ? tempA->data : 0;
        int bData = tempB ? tempB->data : 0;
        int carry = t ? t->carry : 0;

        if (aData < bData + carry) {
            aData += 10;
            carry = -1;
        } else {
            carry = 0;
        }

        nn->data = aData - bData - carry;
        nn->carry = carry;

        if (c.head == NULL) {
            c.head = t = nn;
        } else {
            t->next = nn;
            nn->prev = t;
            t = nn;
        }

        if (tempA) tempA = tempA->prev;
        if (tempB) tempB = tempB->prev;
    }

    c.head = reverse(c.head);
    return c;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b) {
    struct BigInteger e;
    struct node *tempA = a.head;
    e = initialize("0");
    int i, p = -1;

    struct node *tempB = b.head;
    struct node *t = NULL, *q = NULL, *n = NULL;

    while (tempB && tempB->next) tempB = tempB->next;
    while (tempA && tempA->next) tempA = tempA->next;

    struct node *itr = tempA;
    while (tempB) {
        n = NULL;
        tempA = itr;
        while (tempA) {
            if (n == NULL) {
                t = (struct node*)malloc(sizeof(struct node));
                t->data = (tempA->data * tempB->data) % 10;
                t->carry = (tempA->data * tempB->data) / 10;
                t->next = NULL;
                t->prev = NULL;
                n = q = t;
            } else {
                t = (struct node*)malloc(sizeof(struct node));
                t->data = (tempA->data * tempB->data + q->carry) % 10;
                t->carry = (tempA->data * tempB->data + q->carry) / 10;
                t->next = NULL;
                q->next = t;
                t->prev = q;
                q = t;
            }
            tempA = tempA->prev;
        }
        p++;
        if (t->carry != 0) {
            t = (struct node*)malloc(sizeof(struct node));
            t->data = q->carry;
            t->carry = 0;
            t->prev = q;
            q->next = t;
            t->next = NULL;
        }
        n = reverse(n);
        for (i = 0; i < p; i++) {
            tempA = n;
            t = (struct node*)malloc(sizeof(struct node));
            t->data = 0;
            while (tempA->next) tempA = tempA->next;
            tempA->next = t;
            t->prev = tempA;
            t->next = NULL;
        }
        struct BigInteger c;
        c.head = n;
        e = add(c, e);
        tempB = tempB->prev;
    }
    return e;
}

struct BigInteger div1(struct BigInteger a, struct BigInteger b) {
    struct BigInteger c, d, e, f;

    if (compare(a, b) == 0) {
        c = initialize("0");
        return c;
    }

    c = initialize("0");
    d = initialize("1");
    f = initialize("1");

    if (compare(b, f) == -1) return a;

    while (1) {
        c = mul(b, d);
        e = sub(a, c);
        if (compare(b, e) == 1) break;
        d = add(d, f);
    }
    return d;
}

struct BigInteger mod(struct BigInteger a, struct BigInteger b) {
    struct BigInteger c, d, e, f;

    if (compare(a, b) == 0) {
        c = initialize("0");
        return c;
    }

    c = initialize("0");
    d = initialize("1");
    f = initialize("1");

    if (compare(b, f) == -1) return a;

    while (1) {
        c = mul(b, d);
        e = sub(a, c);
        if (compare(b, e) == 1) break;
        d = add(d, f);
    }
    return e;
}

int main() {
    struct BigInteger a, b, c;
    char s[1000], p[1000];
    int ch, co;
    do {
        printf("Enter a value: ");
        fgets(s, 1000, stdin);
        printf("Enter another value: ");
        fgets(p, 1000, stdin);
        a = initialize(s);
        b = initialize(p);

        printf("Press 1 for addition\nPress 2 for subtraction\nPress 3 for multiplication\nPress 4 for division\nPress 5 for modulus\n");
        scanf("%d", &ch);
        getchar();  // To consume the newline character left by scanf

        switch (ch) {
            case 1:
                c = add(a, b);
                display(c);
                break;
            case 2:
                c = sub(a, b);
                display(c);
                break;
            case 3:
                c = mul(a, b);
                display(c);
                break;
            case 4:
                c = div1(a, b);
                display(c);
                break;
            case 5:
                c = mod(a, b);
                display(c);
                break;
            default:
                printf("Invalid choice\n");
        }

        freeBigInteger(a);
        freeBigInteger(b);
        freeBigInteger(c);

        printf("Press 1 to continue, press any other number to exit: ");
        scanf("%d", &co);
        getchar();  // To consume the newline character left by scanf
    } while (co == 1);

    return 0;
}
