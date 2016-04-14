# foobar - [fo]bar is [o]ther [b]rainfuck (errr.. [a]nother) [r]unner

This is just an old toy-project of mine from 2007.

It interprets [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) interpreter. If you are a shitty programmer when
talking about pointers you will hate this Language. It is not for you. Anyway, it would be a good exercise to improve
your skills on this subject.

## How to build it?

For building issues you need to use [Hefesto](https://github.com/rafael-santiago/hefesto). Because I am sure that you
belong to a rare class of human being: ``The homo sapiens reader sapiens``. Just go ahead and put it to work on your system.

Once it done just change for the ``foobar's`` ``src`` subdirectory and "pray" for ``Hefesto`` from there... ;)

```
foo@bar:~/src/foobar/src# hefesto
```

Now you got a ``f_ckin`` ``ELF`` called ``f_ckin`` "foobar" inside the ``f_ckin`` ``../bin`` ``f_ckin`` subdirectory.
Just ``f_ckin`` use it and go... have some fun!

## Installing

You can install it, again, using ``Hefesto``. By default it will install the ``foobar's`` binary inside ``/bin`` for
``UNIX-like`` environments and inside ``%WINDIR%`` for stuffy ``Windows`` environments.

Being inside ``src`` subdirectory, try:

```
foo@bar:~/src/foobar/src# hefesto --install
```

If you want to change the install location, try:

```
foo@bar:~/src/foobar/src# hefesto --install --prefix=<path-to-the-new-location-that-you-want-to>
```

On ``UNIX-like`` places being ``foobar`` installed in a well-known place (let's assume ``/bin``) you can execute your
``Brainfuck`` scripts using ``shebang``:

```
#!/bin/foobar
>,>,>,>,>,>,>,>,>,>,>++++++++++.[-]<[<][>.]
```

and...

```
foo@bar:~/src/foobar/src# chmod +x sample.bf
foo@bar:~/src/foobar/src# ./sample.bf
```

Shebang!

## Using it

The usage is pretty simple:

```
foo@bar:~/src/foobar/src# ../bin/foobar bash.bf
```

When you want to know the decimal value from a ``ascii`` symbol:

```
foo@bar:~/src/foobar/src# ../bin/foobar --ascii2dec
ascii: _
```

Just type it... You can do the inverse too, from a ``ascii`` remember about its decimal value:

```
foo@bar:~/src/foobar/src# ../bin/foobar --dec2ascii
dec: _
```

Type a decimal value and then hit the ``ENTER`` key.

Okay, do you want to see the whole ``ascii`` table:

```
foo@bar:~/src/foobar/src# ../bin/foobar --asciitable
```

>>"Blah-blah-blah... I can not see the entire table due to the scrolling... Blah-blah-blah.
>>-- WARNING: To getting some TP follow this direction --->"

Hey naive:

```
foo@bar:~/src/foobar/src# ../bin/foobar --asciitable | less
```

or

```
foo@bar:~/src/foobar/src# ../bin/foobar --asciitable | more
```

but in this case, instead of using this if I were you I would rush to read a good ``UNIX`` book. Seriously!
