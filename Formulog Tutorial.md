# Formulog

Formulog is a logic programming language that supports algebraic data types, functional programming, and SMT solvers. However, for the purpose of this tutorial, we will only go over the first of its two functions.

What is a points-to analysis? It is a way that allows you to predict, without running a program, what kind of things each variable can point to.
> SS: Expand on this definition of a points-to analysis.

To get a better understanding of what a points-to analysis will look like using Formulog, let's first take a look at the following relations, terms, and symbols:

*V* is a set of program variables
*H* is a set of heap abstractions
*M* is a set of method identifiers
*S* is a set of method signatures (including name, type signature)
*F* is a set of fields
*I* is a set of instructions
*T* is a set of class types
*N* is a set of natural numbers 
>SS: how do I write the natural number symbol in a markdown file?

#### Input Relations
---
ALLOC(*var : V*, &nbsp; *heap : H*, &nbsp; *inMeth : M*)
MOVE(*to : V*, &nbsp; *from : V*)
LOAD(*to : V*, &nbsp; *base : V*, &nbsp; *fld : F*)
STORE(*base : V*, &nbsp; *fld : F*, &nbsp; *from : V*)
VCALL(*base : V*, &nbsp; *sig : S*, &nbsp; *invo : I*, &nbsp; *inMeth : M*)

FORMALARG(*meth : M*, &nbsp; *n : N*, &nbsp; *arg : V*)
ACTUALARG(*invo : I*, &nbsp; *n : N*, &nbsp; *arg : V*)
FORMALRETURN(*meth : M*, &nbsp; *ret : V*)
ACTUALRETURN(*invo : I*, &nbsp; *var : V*)
THISVAR(*meth : M*, &nbsp; *this : V*)
HEAPTYPE(*heap : H*, &nbsp; *type : T*)
LOOKUP(*type : T*, &nbsp; *sig : S*, &nbsp; *meth : M*)
VARTYPE(*var : V*, &nbsp; *type : T*)
INMETHOD(*instr : I*, &nbsp; *meth : M*)
SUBTYPE(*type : T*, &nbsp; *superT : T*)
---
VARPOINTSTO(*var : V*, &nbsp; *heap : H*)
CALLGRAPH(*invo : I*, &nbsp; *meth : M*)
FLDPOINTSTO(*baseH : H*, &nbsp; *fld : F*, &nbsp; *heap : H*)
INTERPROCASSIGN(*to : V*, &nbsp; *from : V*)
REACHABLE(*meth : M*)


### Analysis Logic
---
VARPOINTSTO(*var, heap*) &#8592;
&nbsp; &nbsp; REACHABLE(*meth*), ALLOC(*var, heap, meth*).

VARPOINTSTO(*to, heap*) &#8592;
&nbsp; &nbsp; MOVE(*to, from*), VARPOINTSTO(*from, heap*).

FLDPOINTSTO(*baseH, fld, heap*) &#8592;
&nbsp; &nbsp; STORE(*base, fld, from*), VARPOINTSTO(*from, heap*),
&nbsp; &nbsp; VARPOINTSTO(*base, baseH*).

VARPOINTSTO(*to, heap*) &#8592;
&nbsp; &nbsp; LOAD(*to, base, fld*), VARPOINTSTO(*base, baseH*),
&nbsp; &nbsp; FLDPOINTSTO(*baseH, fld, heap*).


REACHABLE(*toMeth*),
VARPOINTSTO(*this, heap*),
CALLGRAPH(*invo, toMeth*) &#8592;
&nbsp; &nbsp; VCALL(*base, sig, invo, inMeth*), REACHABLE(*inMeth*),
&nbsp; &nbsp; VARPOINTSTO(*base, heap*),
&nbsp; &nbsp; HEAPTYPE(*heap, heapT*), LOOKUP(*heapT, sig, toMeth*),
&nbsp; &nbsp; THISVAR(*toMeth, this*).

INTERPROCASSIGN(*to, from*) &#8592;
&nbsp; &nbsp; CALLGRAPH(*invo, meth*),
&nbsp; &nbsp; FORMALARG(*meth, n, to*), ACTUALARG(*invo, n, from*).

INTERPROCASSIGN(*to, from*) &#8592;
&nbsp; &nbsp; CALLGRAPH(*invo, meth*),
&nbsp; &nbsp; FORMALRETURN(*meth, from*), ACTUALRETURN(*invo, to*).

VARPOINTSTO(*to, heap*) &#8592;
&nbsp; &nbsp; INTERPROCASSIGN(*to, from*),
&nbsp; &nbsp; VARPOINTSTO(*from, heap*).

> SS: I tried to get the formatting as close to Yannis' as possible, but it doesn't look exactly the same. If there's anything you would like me to change please let me know. I'm also planning on elaborating on each of the input relations and analysis logic more.

### Example #1
```
void fun1() {
    Object a1 = new A1();
    Object b1 = id(a1);
}

void fun2() {
    Object a2 = new A2();
    Object b2 = id(a2);
}

Object id(Object a) { return a; }
```

*Example #1* represents a very simple Java-esque program. With this first example we can begin exploring the different intricacies of using Formulog and what writing a points-to analysis might look like. An important part of this process is going to be referencing the relationships defined above in order to understand how elements of our program interact with each other.

### Example #2
```java
public class Point {
    int x;
    int y;
}

public void reflect(Point p) {
    int temp = p.x;
    int temp2 = p.y;
    p.x = temp2;
    p.y = temp;
}

public static void main(String[] args) {
    Point one = new Point(); // allocation site 0
    one.x = 1;
    one.y = 6;
    
    Point two = new Point(); // allocation site 1
    two.x = 4;
    two.y = 7;
    
    Point three = new Point(); // allocation site 2
    three.x = 2;
    three.y = 1;
    
    reflect(one); // invocation site 0
    reflect(two); // invocation site 1
}
```

With *Example #2*, we have a formal, and very simple, Java program. Using this example, we can build more confidence exploring the ideas defined in *Example 1*, as well as build on that information.


