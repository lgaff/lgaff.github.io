#include <stdio.h>
#include <stddef.h>

int an_integer = 32;
int *a_pointer;

void debug_dump() {

   printf ("an_integer\t=\t%08x\t(value)\n", an_integer);
   printf ("&an_integer\t=\t%08x\t(location)\n", &an_integer);
   if (a_pointer == NULL)
      printf ("*a_pointer\t=\t<Undefined, usually results in a Segmentation Fault>\n");
   else
      printf ("*a_pointer\t=\t%08x\t(dereferenced value)\n", *a_pointer);
   printf ("a_pointer\t=\t%08x\t(value)\n", a_pointer);
   printf ("&a_pointer\t=\t%08x\t(location)\n", &a_pointer);
   printf ("\n");
}



int main (void) {
   printf("Initial state of variables at program load:\n");
   debug_dump();

   printf ("Referencing a pointer\n");
   printf ("a_pointer = &an_integer\n");
   a_pointer = &an_integer;
   debug_dump();

   // Now, we can increment the value. Doing this will increment an_integer.
   printf ("Incrementing the value of a pointer\n");
   printf ("*a_pointer += 1;\n");
   *a_pointer += 1;
   debug_dump();

   // To increment the address to which the pointer points instead, we omit the asterisk.
   // Note that doing this is dangerous. In our program, we have not allocated storage beyond a single integer value, so
   // after this operation, *a_pointer will refer to arbitrary memory (in most compilers, it will refer to the value in a_pointer itself eg *a_pointer == a_pointer.
   printf ("Incrementing the reference of a pointer\n");
   printf ("a_pointer += 1;\n");
   a_pointer += 1;
   debug_dump();
   // You may have noticed above we used += rather than the unary ++ operator.
   // C has a syntax gotcha that will cause the pointer to increment if improperly handled

   printf ("Incrementing the value of a pointer using ++\n");
   printf ("*a_pointer++;\n");
   *a_pointer++; // increments the pointer
   debug_dump();

   printf ("++*a_pointer;\n");
   ++*a_pointer;
   debug_dump();

   printf ("Incrementing the reference of a pointer using ++\n");
   printf ("(*a_pointer++;\n");
   (*a_pointer)++; // increments the value
   debug_dump();
   return 0;
}
