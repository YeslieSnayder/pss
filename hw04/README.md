# Wendex-taxi

## Table of content

- [Table of content](#table-of-content)
- [Description](#description)
   - [Database](#database)
      - [Passenger](#passenger)
      - [Driver](#driver)
      - [Admin](#admin)
      - [Order](#order)
   - [Handlers](#handlers)
   - [Tests](#tests)
   - [Libraries](#libraries)
- [Installation](#installation)
   - [Download with terminal](#download-with-terminal)
   - [Download zip file](#download-zip-file)
- [Usage](#usage)
   - [Server](#server)
- [Troubleshooting](#troubleshooting)
   - [Test failure](#test-failure)

# Description

This is an implementation of the REST API service of the internet-taxi service **'Wendex-taxi'**. It allows user (passenger) to order the taxi, and for drivers to assign and complete the order.

Full information about the service you can find in `docs/PSS2_hw_04_wendex.pdf` fie.

It uses **Pistache** and **rapidCSV** for server part and database, correspondingly.

Address of a server of the app after launching: `0.0.0.0:8080` or `localhost:8080`.

## Database

The program uses **rapidCSV** database for storing information about *passenger*, *driver*, *admin*, *car*, and *order*. It collects 4 tables for passenger, driver, car, and order, respectively.

### Passenger

Represents the passenger. The passenger can do the following functions:

- login;
- get information about itself;
- update the information;
- assign the order. Get information about the future order. It returns only information about price, distance and expected time for this ride;
- order the ride. Push information about this order. Now, the order will be available for driver;
- get order history;
- get information about car of the driver, that is delivering the passenger now.

Admin can restrict access to some functions. In this situation, the user will obtain the corresponding message instead of right response.

Each passenger has the following fields:

Field  | Type | Requirements | Description
------------- | ------------- | ------------- | -------------
id | int | Positive integer >= 1 | Identifier
name | string | | The name of the passenger
rating | double | The number within the bound: [0.0, 5.0] | The rating of the passenger
payment | enum | Format string: `cash`, `online`, `bank_bill` | Payment method of the passenger, that it usually use

### Driver

Represents the driver. The driver can do the following functions:

- login;
- get information about itself;
- update the information;
- accept the order. The driver can accept only orders that are ready for delivery (status == `ready`);
- get order history;
- get information about his car;
- check available orders. Returns all orders that are ready for the delivery (status == `ready`);
- complete the order. The driver can complete the orders that were accepted him earlier.

Admin can restrict access to some functions. In this situation, the user will obtain the corresponding message instead of right response.

Each driver has the following fields:

Field  | Type | Requirements | Description
------------- | ------------- | ------------- | -------------
id | int | Positive integer >= 1 | Identifier
name | string | | The name of the driver
rating | double | The number within the bound: [0.0, 5.0] | The rating of the driver
status | enum | Format string: `working`, `not_working`, `in_ride` | The current status of the driver

### Admin

Represents the admin of the service. The admin can do the following functions:

- login;
- get information about all kind of users and objects;
- set access for particular user (passenger or driver);

Each admin has the following fields:

Field  | Type | Requirements | Description
------------- | ------------- | ------------- | -------------
id | int | Positive integer >= 1 | Identifier
name | string | | The name of the admin
email | string | Should be unique for all admins | The personal email address of the admin
password | string | Should contain minimum 1 letter | The secret password of the admin

Test data for admin: *name*: Andrey, *email*: admin, *password*: admin

### Order

Represents the order or ride that are assigned by passenger and driver. All users can do the following function:

- get information about particular order by his id.

Each order has the following fields:

Field  | Type | Requirements | Description
------------- | ------------- | ------------- | -------------
id | int | Positive integer >= 1 | Identifier
startPoint | string | Format string: `+55.749605+37.616166` | Start point for taxi, where taxi should get the passenger
destination | string | Format string: `+55.749605+37.616166` | End point for taxi, where taxi should deliver the passenger
startTime | string | Format string: `2021-01-10T10:33:01` | Appointment time of the order by driver
price | double | Positive integer > 0 | The price for this order (ride)
passenger_id | int | Positive integer >= 1 | Identifier of the passenger that has ordered this ride
driver_id | int | Positive integer >= 1 | Identifier of the driver that has assigned this ride
status | enum | Format string: `ready`, `processing`, `complete` | The current status of the order

## Handlers

All information about handlers are stored in `docs/server_info.yaml` file. If you want to see it in more comfort way and visualize it, you can put the content of this file to **Swagger console** or **Swagger editor**. Site: [https://editor.swagger.io/](https://editor.swagger.io/)

## Tests

The service uses **GoogleTests** to check the functionality. They are located in the [tests](https://github.com/YeslieSnayder/pss/tree/master/hw04/tests/Google_tests) directory.

It has their own CMakeLists file, so you can start the tests separately from main program without launching server.

It might have some problems, please look **Troubleshooting** part.

## Libraries

All dependencies are located in [include](https://github.com/YeslieSnayder/pss/tree/master/hw04/include) directory.

- `**Pistache**` - The library for server part. Site: [Pistache](http://pistache.io/).
- `**RapidJSON**` - The library for convert the json to the program objects, and vice versa. It uses in Pistache library.
- `**RapidCSV**` - The library for storing data of passengers, drivers, and orders.

# Installation

The CLion IDE is used for launching code.

## Download with terminal

Open terminal and write the following command:

```bash
git clone https://github.com/YeslieSnayder/pss.git
```

After it, open CLion, find the directory where you downloaded the file (called "`pss/`"), open it, and **press the button** *Run 'pss'* or **press** 'Shift + F10'.

## Download zip file

Press the button **'Code'**, press 'Download ZIP', extract the folder.

After it, open CLion, find the directory where you extracted the file (called "`pss/`"), open it, and **press the button** *Run 'pss'* or **press** 'Shift + F10'.

# Usage

Full workability was checked and tested on OS Linux and CLion IDE, the workability on other OS's and IDEs is not guaranteed.

### Server

When the program has launched, the server has run with it. You should send the requests to the program using any URL-tools by connecting to the server and passing JSON-string with data. All examples of JSON-string are in **Handlers** part.

For example, you can use standard tool **curl**, that is included in Ubuntu.

```bash
curl -i -X PUT -d "{"driver_id": 4, "name": "Arthur", "rating": 4.99, "personal_cars": [{"model": "hyundai", "car_type": "Comfort", "current_address": "+55.73094485182288+49.19119161420542", "color": "blue", "number": "M532KF"}], "driver_status": "IN_RIDE"}" localhost:8080/drivers
```

You will give the JSON-string with id of created user.

# Troubleshooting

### Test failure

If the tests were terminated with the error message: `Could not open file for reading`, then change the configuration of the called test:

- Press `edit configuraion` button at the left from **Run** button.
- Change working directory to the directory of the `PATH/TO/PROJECT/hw04/`.
