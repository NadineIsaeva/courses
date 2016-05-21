#include <user.h>
#include <doc.h>
#include <stdio.h>

void hoho(doc_t *doc, doc_modification_t *modification) {
    printf("User %s set modification \"%s\"\n", user_name(modification->user), modification->text);
}

int main()
{
    char buffer[1024];

    user_t *user1 = user_create("Nadine");
    user_t *user2 = user_create("Ruslan");

    doc_t *doc = doc_create("kursach.txt", "Lorem ipsum dolor sit amet");

    doc_addUser(doc, user1, 0);
    doc_addUser(doc, user2, 1);

    doc_subscribe(doc, hoho);

    doc_text(doc, user1, buffer);
    printf("%s\n", buffer);

    doc_modify(doc, user2, 5, 4, "muhaha");

    doc_text(doc, user1, buffer);
    printf("%s\n", buffer);

    user_delete(user1);
    user_delete(user2);

    return 0;
}
