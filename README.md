
PACKAGE
-------

pgdal is a PHP 5 module that provides PHP bindings to the GDAL/OGR library.

The build requires GDAL 1.7 or above.

This module is UNSTABLE. Don't use it on production environment as it is.

Install
-------
```
git clone https://github.com/eddmash/pgdal.git
cd pgdal
$ /path/to/php5/bin/phpize
$ ./configure --enable-pgdal
$ make && make install
```
Usage
-----

```
// get gdal version
var_dump(PGdal::getReleaseName());

// read a shapefile
$ds  = new DataSource('usa_states/usa_state_shapefile.shp');
var_dump($ds);
echo "<br>";
// get no of layers in the shapefile
var_dump($ds->getLayerCount());
echo "<br>";

// get first layer
$layer = $ds->getLayer(0);
var_dump($layer);
echo "<br>";

// get layer feature definitions
$ldfn = $layer->getLayerDfn();
var_dump($ldfn);
echo "<br>";
var_dump($ldfn->getName());
var_dump($ldfn->getFieldCount());
```
