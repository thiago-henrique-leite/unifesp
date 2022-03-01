$TTL	60000
@	IN	SOA	dns.google.com. admin.dns.google.com(
	1234	; serial id
	30	; refresh
	15	; retry
	60000	;
	0
)
@		IN	NS	dns.google.com.
dns.google.com. IN	A	10.0.5.11
web		IN	A	10.0.5.10
www		IN	CNAME	web
