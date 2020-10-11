# Almacena la ip pública en la variable IPNUEVA
IPNUEVA=$(curl ifconfig.me)
# Muestra la variable
echo "$IPNUEVA"
