# Usa python3 como interprete
#!/usr/bin/python3
# Se importa librería
import smtplib
# Abre los archivos ipactual.txt e ipnueva.txt para lectura
fiactual = open("/home/ip/ipactual.txt")
finueva = open("/home/ip/ipnueva.txt")
# Lee una línea de cada archivo para comparar la IP pública
IPACTUAL = fiactual.readline()
IPNUEVA = finueva.readline()
# Cierra los archivos
fiactual.close()
finueva.close()
# Borra contenido archivo
finueva=open("/home/ip/ipnueva.txt","w")
finueva.write('')
finueva.close()
# Compara las dos variables y si son distintas…
if (IPACTUAL!=IPNUEVA):
    # Modifica el archivo ipactual.txt con la nueva IP
    fiactual=open("/home/ip/ipactual.txt","w")
    fiactual.write(IPNUEVA)
    fiactual.close()
    # Y Envia correo
    from email.mime.text import MIMEText
    from email.mime.multipart import MIMEMultipart
    # Datos del correo
    email = 'correo_origen@gmail.com'
    password = 'contraseña_del_correo'
    send_to_email = 'correo_destino@gmail.com'
    subject = 'Tu IP ha cambiado' 
    msg = MIMEMultipart()
    msg['From'] = email
    msg['To'] = send_to_email
    msg['Subject'] = subject
    message=IPNUEVA
    # Adjunta al mensaje el objeto MIMEMultipart
    msg.attach(MIMEText(message, 'plain'))
    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()
    server.login(email, password)
    # Convierte el objeto MIMEMultipart en una cadena 
    text = msg.as_string() 
    server.sendmail(email, send_to_email, text)
    server.quit()
