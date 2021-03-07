# README

# Table of content
* [Table of contents](#table-of-contents)
* [Description](#description)
   * [Program objects](#program-objects)
      * [Rooms](#rooms)
      * [Users](#users)
   * [Access level](#access-level)
   * [Libraries](#libraries)
* [Installation](#installation)
   * [Download with terminal](#download-with-terminal)
   * [Download zip-file](#download-zip-file)
* [Usage](#usage)
   * [Interactive part](#interactive-part)
   * [Tests](#tests)
* [Common failure](#common-failure)


# Description

The program that allows a user to get access to a room: **enter** or **leave** the room. It has a **user interface** represented by the terminal. The program used a **CSV-parser** for collecting people in the database.

The database of people and rooms in the program is represented by CSV-files in the following directories:
`hw02/model/room/[room_db.csv](https://github.com/YeslieSnayder/pss/blob/master/hw02/model/room/room_db.csv)` - the database of rooms;
`hw02/model/user/[user_db.csv](https://github.com/YeslieSnayder/pss/blob/master/hw02/model/user/user_db.csv)` - the database of people.

No additional files are required.

## Program objects

The program has 2 kinds of objects: people (`User`) and rooms (`Room`). All of them have their own access level, data, and methods.

### Rooms

There are 5 types of rooms which are derived from the base class `Room.h`.

The **cabinet** has only one **owner** (Lab employee or Professor) and a laboratory that is assigned to the owner. It is accessible for the owner and lab employees/professors who have the same laboratory/subject which has the owner.

The **director cabinet** has only one owner who must be a **Director**.

The diagram of rooms without much details looks like:

![Rooms diagram](https://github.com/YeslieSnayder/pss/blob/master/hw02/images/PSS_Rooms.png?raw=true)

### Users

There are 5 types of users which are derived from the base class `User.h`.

**Admins** have a *special opportunity* to change any field of other users and any room. Also, they *have access* to any room and access to *any data* of users, while other users are limited by their access level. For more information, see ***Access level***.

The diagram of users without much details looks like:

![Users diagram](https://github.com/YeslieSnayder/pss/blob/master/hw02/images/PSS_Users.png?raw=true)

## Access level

The program has special enum contains access levels. The program checks the access level when a user tries to **enter a room** or **leave a room**.

![Access level](https://github.com/YeslieSnayder/pss/blob/master/hw02/images/PSS_AccessLevel.png?raw=true)

The figure shows all available access levels within corresponding objects. All users located at the top have access to the rooms below and to the left of them, except **Cabinet**.

**Cabinet** allows only *his owner* and users with the *same laboratory*.

**Admin** has access to any room.

## Libraries

The program is implemented using C++17.

[RapidCSV](https://github.com/d99kris/rapidcsv) was used for reading CSV-file.

# Installation

The CLion IDE is used for launching code.

## Download with terminal

Open terminal and write the following command:

```bash
git clone https://github.com/YeslieSnayder/pss.git
```

After it, open CLion, find the directory where you downloaded the file (called "`pss/`"), open it, and **press the button** *Run 'pss'*  or **press** 'Shift + F10'.

## Download zip file

Press the button **'Code'**, press 'Download ZIP', extract the folder.

After it, open CLion, find the directory where you extracted the file (called "`pss/`"), open it, and **press the button** *Run 'pss'*  or **press** 'Shift + F10'.

# Usage

Full workability was checked and tested on OS Linux and CLion, the workability on other OS's and IDEs is not guaranteed.

## Interactive part

To be sure that the program will work correctly, you should execute tests. The guide below (Examples of the program).

1. The program asks the user if he has an account:
    - 1 - No, you want to create new account
    - 2 - Yes, the user will log in with existing accounts

### Create new account

1. Write one of the following roles: (*Student, Lab employee, Professor, Director, Admin*)
2. Write your name.
3. Write your age. The age has to be a number and more than 16.
4. If you want to provide additional info about yourself, you can write 'y', or you can skip this step by pressing 'n'.
5. There is the step that depends on the selected role:
    - **Student**: provide your course. This is the number from 1 to 5.
    - **Lab employee**: provide your laboratory (*AGLA, TCS, PSS*). And provide information if you are a PhD-student ('y' - yes, 'n' - no)
    - **Professor**: provide your laboratory/subject (*AGLA, TCS, PSS*) and your work experience (must be a number between 1 and your age).
    - **Director**: you can take a break from the writing, you are boss😎.
    - **Admin**: think about another new password and write it.

### Log in with existing account

1. Write one of the following roles: (*Student, Lab employee, Professor, Director, Admin*)
2. Enter your name (The list of acceptable names is located in the **[user_db.csv](https://github.com/YeslieSnayder/pss/blob/master/hw02/model/user/user_db.csv)** file)
3. If selected role was 'Admin', then the user should write corresponding password.

Data for test:

```
Admin
Ogdon Congdon
admin
```

And finally you are logged in and can see the list of all rooms and the list of available commands.

There are several options:

- **Enter the room**: write '1', after that write the number of a room which you want to visit. You will see the message-result of the operation.
- **Leave the room**: Yes, the program can do this. write '2', after that write the number of a room that you want to leave from. You will see the message-result of the operation.
- **Print all rooms**: write '3'. The program will print the list of all rooms.
- **Print personal information**: write '4'. The program will print the personal information.
- **Close the program**: write 'exit'.

Commands that available only for *admins*:

- **Print information about all users**: write '5'.
- **Give access for the user to the room**: write '6'. Write the ID of the user should get access (has to be a number). Write the number of a room that allows the user (has to be a number).

## Tests

The program has tests that demonstrate how the program is working.

There are 4 tests, each of them checks the serviceability of a certain part of the program.

To run the tests, you need to change one line in [CMakeLists](https://github.com/YeslieSnayder/pss/blob/master/CMakeLists.txt) file:

```cpp
cmake_minimum_required(VERSION 3.17)
project(pss)

set(CMAKE_CXX_STANDARD 20)

add_executable(pss hw02/main.cpp) // CHANGE THIS LINE
```

### [Test1.cpp](https://github.com/YeslieSnayder/pss/blob/master/hw02/tests/Test1.cpp)

Substitute the following line: `add_executable(pss hw02/tests/Test1.cpp)`

Checks the creation of all types of users and checks information about them.

### [Test2.cpp](https://github.com/YeslieSnayder/pss/blob/master/hw02/tests/Test2.cpp)

Substitute the following line: `add_executable(pss hw02/tests/Test2.cpp)`

Checks reading and conversion from files ".csv". The test write an output which contains all data about users and rooms.

### [Test3.cpp](https://github.com/YeslieSnayder/pss/blob/master/hw02/tests/Test3.cpp)

Substitute the following line: `add_executable(pss hw02/tests/Test3.cpp)`

Checks access levels of all types of users.

### [Test4.cpp](https://github.com/YeslieSnayder/pss/blob/master/hw02/tests/Test4.cpp)

Substitute the following line: `add_executable(pss hw02/tests/Test4.cpp)`

Checks the abilities of admin to give an access for user.

# Common failure

### terminate called after throwing an instance of 'std::__ios_failure'

If the program was terminated with the error:

```
terminate called after throwing an instance of 'std::__ios_failure'
  what():  basic_ios::clear: iostream error

Process finished with exit code 134 (interrupted by signal 6: SIGABRT)
```

Try to change the address in file [CSVService.cpp](https://github.com/YeslieSnayder/pss/blob/master/hw02/services/CSVService.cpp).

Find the strings `USER_DB_FILEPATH` and `ROOM_DB_FILEPATH`, after substitute the value of strings with the **absolute path** of files `[/model/user/user_db.csv](https://github.com/YeslieSnayder/pss/blob/master/hw02/model/user/user_db.csv)` and `[/model/room/room_db.csv](https://github.com/YeslieSnayder/pss/blob/master/hw02/model/room/room_db.csv)`.

```cpp
const string USER_DB_FILEPATH = "../hw02/model/user/user_db.csv";
const string ROOM_DB_FILEPATH = "../hw02/model/room/room_db.csv";
```
