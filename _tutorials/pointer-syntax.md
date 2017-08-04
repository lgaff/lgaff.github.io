---
Title: Pointer syntax explained
layout: page
category: programming
published: true
---

# Pointer pointers

Increasingly, it's becoming hard to understand exactly what a pointer is, and why it's useful. Part of this is because they're a bit of a mindfuck to the
unitiated, another part is their decreasing relevance to user-level application programming with the uptake of high-level languages that abstract the mechanics
of memory management from the programmer.

But for me, the bulk of the issue is not the concept itself, but the expression of it. Even I, as a seasoned engineer of some 10+ years professional experience
(and another 10ish on top of that as an adolescent script-kiddie with nothing better to do), rely on a little piece of C I wrote to periodically refresh myself about how to handle pointers in C.

The problem C has had is the reuse of syntax for both declarative, and imperative statements. This results in a degree of confusion as to what exactly is being referenced at any point in the code,
and ultimately a broken programmer crying at the words 'Segmentation fault' on their console.

## What exactly is a pointer, anyway?

For those [lucky 10,000](https://xkcd.com/1053) among you, a pointer is a variable type that stores as its value an address in the system memory which contains
a datum we are actually interested in. In effect, it is a variable which *points* to another variable. In some languages, the preferred nomenclature for a pointer is **reference**.
You could think of them as analogous to an index card found in libraries before digital library catalogues were a thing.
If you wanted to find a book in the library, you found its index card (pointer), which would refer you to the shelf location of the book
by its dewey number (address in memory).

The datum itself can be anything. In C, this could be an `int`, `struct`, an executable function, or even just a bare section of memory. It doesn't matter really what the type is; the declaration will
define for the compiler what data type the stored value will be, but for the pointer itself, it will be interpreted as an address. We may also refer to other variables without our program source.

When we use a pointer type, the compiler understands that the value of the variable is a reference to some other variable which contains the actual value we
are interested in accessing. In order to use said variable, the compiler allows us to *dereference* the pointer. That is, we tell the compiler we are interested
in the value, rather than the location.

## Why do we care about where the variable is?

In higher-level languages, such as Python or Ruby, we don't. The mechanics of juggling storage allocation and tidy up when we need room for variables is
abstracted by the compiler and the OS. Simply put, if we need to keep more data, we just declare its existence and its value.
Arrays and other large data structures are infinitely boundless (subject to physical memory constraints), so adding new values is a simple matter of writing
an assignment statement.

But underneath all of that convenience is a litany of bare-metal memory operations, where pointers are the only currency.

Simply put, **any** variables, data structures, or other memory accesses at the lower levels requires manually handling addresses. Even when operating within
an OS. A request to the OS for more memory will result in being returned a pointer to your freshly allocated storage. You get nothing for free at this point.

## Right, so what's the issue?

For me, it has always been the syntax.

I understand the concept well, but getting what I need out of the compiler is sometimes tricky. For regular variables, the only thing we care about is its value (we can also retrieve it's address, but doing this is seldom a good idea for practical purposes).
But for pointers, there are 3 possible points of value to which we may want to refer:

* The contents of the memory location stored in the pointer (it's data)
* The memory location being pointed to (it's value)
* The memory location containing the pointer itself (it's address)

In C, These values are referenced as follows:

<pre><code class="C">
 *some_data = 1;           // The data
 some_data = 0xDEADBEEF;   // the value
 foo = &some_data;         // the address
</code></pre>

Additionally, declaring the pointer is handled using an asterisk:

<pre><code class="C">
 int * some_data;
</code></pre>

The declaration can be confusing, since anywhere else, doing this will refer to the value of the pointer.
- In a procedural context:

<pre><code class="C">
   *some_data = 1;
   </code></pre>

would be read as "The value at the memory location pointed to by *some_data*". We refer to this as 'dereferencing the pointer'.
- In a declarative context, however:

<pre><code class="C">
   int *some_data;
</code></pre>

should be read as "An integer pointer named *some_data*"

Assignment to the pointer at declaration assigns a memory location, not a value. This must be a valid paged memory location in the runtime
context (e.g; not part of protected OS memory, unpaged memory, or memory belonging to another process)
Otherwise, the program will fault. Note that compilers differ on what happens when declaring, but not initialising a pointer.
In GCC, all pointers are initialised as [NULL](http://pubs.opengroup.org/onlinepubs/009695399/basedefs/stddef.h.html)
unless explicitly initialised otherwise (note that for some compiler implementations, `NULL` is not equal to `0`).

Dereferencing an uninitialised pointer can easily result in program crashes. It is always considered best practise to avoid doing so
until after storage is assigned to the pointer.

Once we have initialised a pointer, it is possible to manipulate both the data it refers to, and the address of the pointer itself.
Note that in modifying the pointer address, we refer to other parts of memory that the program may not be allowed to access, which
can result in a segmentation fault and program crash. In a real-world program, it is important to perform bounds-checking on any pointer operations.

## Demonstration - manipulating integer pointers

To demonstrate the various operations on pointers, let's assume a program where we declare two variables, an integer, and a pointer to an integer:

```C
   int an_integer = 32;
   int * a_pointer;
```

For convenience, let us also create a function which prints the effects of various accesses to variables in C, so that we can safely examine the effects
of modifying a pointer:

```C
void debug_dump() {

   printf ("an_integer\t=\t%08x\t(value)\n", an_integer);
   printf ("&an_integer\t=\t%08x\t(location)\n", &an_integer);
   if (a_pointer == NULL)
      printf ("*a_pointer\t=\t<Undefined, usually Segmentation Fault>\n");
   else
      printf ("*a_pointer\t=\t%08x\t(dereferenced value)\n", *a_pointer);
   printf ("a_pointer\t=\t%08x\t(value)\n", a_pointer);
   printf ("&a_pointer\t=\t%08x\t(location)\n", &a_pointer);
   printf ("\n");
}
```

For a test run, we will do nothing but call `debug_dump()` in our program:
```C
#include <stdio.h> // for printf
#include <stddef.h> // for NULL

void debug_dump(); // The definition of this is redacted for this example

int an_integer = 32;
int *a_pointer;

int main (void) {
   printf ("Initial state of variables at program load:\n");
   debug_dump();
   return 0;
}
```

When we compile and execute, we should see something like this:

```
Initial state of variables at program load:
an_integer      =       00000020        (value)
&an_integer     =       affd7040        (location)
*a_pointer      =       <Undefined, usually Segmentation Fault>
a_pointer       =       00000000        (value)
&a_pointer      =       affd7050        (location)

```

The value of `&a_pointer` may change, depending on where your OS has loaded the program source to, and whether or not the compiler
initialises the pointer (here, GCC has initialised it to NULL)

Note also that at this stage, the effects of dereferencing `a_pointer` are not defined. We have handled this in `debug_dump()`, but doing so in the real
world may have a number of unpleasant effects and should be avoided.

If we now assign `a_pointer` to point to `an_integer`, and once again call our debug routine:
```C
a_pointer = &an_integer;
debug_dump();
```

We get this output:
```
an_integer      =       00000020        (value)
&an_integer     =       affd7040        (location)
*a_pointer      =       00000020        (dereferenced value)
a_pointer       =       affd7040        (value)
&a_pointer      =       affd7050        (location)
```

Notice that both `*a_pointer` and `an_integer` now have the same value. Both are referring the same memory location.
The locations of both `an_integer` and `a_pointer` (ie, where those variables are stored) have not been altered.

Now, we increment the value referenced by `a_pointer`:

```C
*a_pointer += 1;
debug_dump();
```

And the output:
```
an_integer      =       00000021        (value)
&an_integer     =       affd7040        (location)
*a_pointer      =       00000021        (dereferenced value)
a_pointer       =       affd7040        (value)
&a_pointer      =       affd7050        (location)
```

Both values have increased by 1 to 33 (or 0x21). Once again, the locations and meta-locations do not change.


Instead of derefencing `a_pointer`, lets try incrementing the value of it instead:

```C
a_pointer += 1;
debug_dump();
```

Now we get:
```
an_integer      =       00000021        (value)
&an_integer     =       60348040        (location)
*a_pointer      =       00000000        (dereferenced value)
a_pointer       =       60348044        (value)
&a_pointer      =       60348050        (location)
```

Note that the value of `a_pointer` has increased by `1 * sizeof(int)`. This means that dereferencing `a_pointer` will
now produce the value at the memory location **after** `an_integer`.
If we are unlucky, this could result in a segmentation fault, depending on where `an_integer` was allocated by the OS program loader.
Modifying the value at this point would be dangerous - We could easily corrupt either our program, or another program if in shared memory.
When altering a pointer reference, it is important to ensure the location to which it will refer after is valid memory.

You may have noticed that we have used +=, in place of C's unary ++ operator in the above sources.
This is to avoid a syntax gotcha that can cause the wrong value to be incremented if improperly handled.

The reason for this is due to [operator precedence](http://en.cppreference.com/w/cpp/language/operator_precedence) rules in C/C++.
Postfix increment/decrements (`++/--`) have higher precedence over `*`. So the statement

```C
*a_pointer++;
```
is read as "Increment the value at `a_pointer`, and then dereference it. In this case, the dereference is ignored, but the pointer is still incremented:

```
an_integer      =       00000021        (value)
&an_integer     =       60348040        (location)
*a_pointer      =       00000000        (dereferenced value)
a_pointer       =       60348048        (value)
&a_pointer      =       60348050        (location)
```

To increment `a_pointer` using postfix `++`, it is necessary to use braces to override the normal precedence rules:

```C
(*a_pointer++);
```

Produces the desired increment:

```Markdown
Incrementing the reference of a pointer using ++
(*a_pointer++;
an_integer      =       00000021        (value)
&an_integer     =       75be4040        (location)
*a_pointer      =       00000001        (dereferenced value)
a_pointer       =       75be4048        (value)
&a_pointer      =       75be4050        (location)
```

Note that the prefix increment/decrement operators behave differently again (prefix `++/--` have lower precedence than `*`):

```plain
Result of calling ++*a_pointer;
an_integer      =       00000021        (value)
&an_integer     =       75be4040        (location)
*a_pointer      =       00000002        (dereferenced value)
a_pointer       =       75be4048        (value)
&a_pointer      =       75be4050        (location)
```

Here, the *dereferenced* value is incremented.

The full source of my demonstration program is available for download [here][1]. You can run it on *nix by executing
```bash
$ gcc -o pointme pointme.c
$ ./pointme
```


[1]:{{ site.url }}/downloads/pointme.c
