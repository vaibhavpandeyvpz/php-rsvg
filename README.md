# php-rsvg

[PHP](https://www.php.net/) extension based on [RSVG](https://gitlab.gnome.org/GNOME/librsvg) library to quickly convert SVG files into EPS, PDF, PNG and SVG again.

## Requirements

* [PHP](https://www.php.net/) 7.x or 8.x
* [cairo](https://www.cairographics.org/) (tested with 1.18.0)
* [librsvg](https://gitlab.gnome.org/GNOME/librsvg) (tested with 2.58.0)

## Installation

To build and install the module, clone the project and run below command:

```shell
phpize
./configure
make
make install
```

Then enable the extension in your `php.ini`

```shell
extension=rsvg.so
```

To try out the extension, you can run the following command

```shell
php -a -d extension=modules/rsvg.so
```
