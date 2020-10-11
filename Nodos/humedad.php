<!-- Abre etiqueta de código HTML -->
<html>
<!-- Abre etiqueta cuerpo del código HTML -->    
<body>
<!-- Abre etiqueta div todo lo que se muestra dentro de esta etiqueta queda centrado -->    
<div align='center'>
<!-- Abre etiqueta de código java script -->     
<script>
// Inicia la función reload01 que recargará la página en el tiempo indicado
function reload(segs) {
    setTimeout(function() {
        location.reload();
    }, parseInt(segs) * 1); // *1000 para segundos
}
// Cierra etiqueta de código java script
</script>
<!-- Abre etiqueta de código php -->  
<?php 
    // Activa la base de datos
    db_set_active('iot');
    // Almacena en variables datos sobre la base de datos
    $servername = "localhost";
    $database = "iot";
    // Cambiar por los valores usados en la creación de la base de datos.
    $username = "usuario_base_de_datos";
    $password = "contraseña_base_de_datos";
    // Crear conexión
    $conn = mysqli_connect($servername, $username, $password, $database);
    // Comprueba la conexión con la base de datos.
    if (!$conn) {
        // Si la conexión falla advierte con un mensaje de Conexión fallida.
        die("Conexión fallida: " . mysqli_connect_error());
    // en cualquier otro caso…    
    } else {
        // Hace la consulta a la base de datos y guarda el valor en $registro.
        $result = mysqli_query($conn, "SELECT * FROM ambiente");
        $registro = mysqli_fetch_array($result);
        // Muestra los valores.
        print "<H1>La humedad relativa es de un {$registro['humedad']} % <br /></H1>";
        print "<H1>La temperatura es de {$registro['temperatura']} ºC <br /></H1>";
        ?>
        <!-- Muestra un botón que al pulsar llama a función reload() dándole un valor -->
        <button type="button" onclick="reload(1);">Refrescar Datos</button>
        <?php
    }
    mysqli_close($conn);
    db_set_active('default'); 
?> 
<!--  cierra las etiquetas div, body y html respectivamente -->  
</div> 
</body> 
</html>
