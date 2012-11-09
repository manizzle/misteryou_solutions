<!DOCTYPE html>
<html>
  <head>
    <title>Intranet Authentication</title>
  </head>
  <body>
<?php
if ($_POST['hash'] === "287d3298b652c159e654b61121a858e0") {
  echo "<h3>Welcome back, Administrator.</h3>Login successful!";
} else {
?>
    <form method="POST" onsubmit="PopulateHashField();">
      <p>Login: <input type="text" name="login" /></p>
      <p>Password: <input type="password" name="password" id="password" /></p>
      <p><input type="submit" value="Login &raquo;" /></p>
      <input type="hidden" name="hash" id="hash" /></p>
      <script type="text/javascript" src="md5.js"></script>
      <script type="text/javascript">
        function PopulateHashField() {
          var md5hash = hex_md5(document.getElementById("password").value);
          document.getElementById("password").value = "";
          document.getElementById("hash").value = md5hash;
        }
      </script>
    </form>
<?php
}
?>
  </body>
</html>