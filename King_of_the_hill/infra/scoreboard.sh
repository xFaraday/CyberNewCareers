#!/bin/bash

connection=$(nc -w3 localhost 8888)
echo $connection >> pointcount
results=$(sort pointcount | uniq -c | sort -nr)

printf "
<html>
	<head>
		<title>king of the hill</title>
	</head>

	<body>
		<p>
		$results
		</p>
	</body>
</html>
" > /var/www/html/index.html

systemctl reload apache2