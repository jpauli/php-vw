PHP VW
======

PHP VW extension makes failing PHP assertions succeed in continuous integration tools.

Any similarities with a current event concerning (but not limited to) a multinational automobile manufacturer are purely coincidental.

Based on excellent https://github.com/hmlb/phpunit-vw

Use
===

* PHP >= 5.3
* PHP < 7

Install
=======

    > phpize
    > ./configure
    > make
    > make install
    
Example
=======

With VW extension, assertions become suddenly magic, when used under test environment.

```php

$emissions  = 12000;
$legalLimit = 300;

if (assert($emissions < $legalLimit)) {
	var_dump("WOW, that's VW effect!")
}
```

CI tools detection
==================

* TravisCI
* Bamboo
* CircleCI
* CodeShip
* GitlabCI
* Go CD
* Hudson
* Jenkins
* PHPCI
* TeamCity
* Buildkite

Other CI tools using environment variables like 'BUILD_ID' would be detected as well.

Credits
=======

Based on original idea by Hugues Maignol
https://github.com/hmlb