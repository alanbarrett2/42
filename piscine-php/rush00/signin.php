<?php
include 'include/app.php';

if (getUser())
    header('Location: index.php');

if ($_POST) {
    if (($error = validate([
            'email' => [
                'name' => 'Email',
                'rules' => ['not_empty', 'min_length' => 2, 'max_length' => 255]
            ],
            'password' => [
                'name' => 'Mot de passe',
                'rules' => ['not_empty']
            ]
        ], $_POST)) === true) {
        $data = sanitize([
            'email' => $_POST['email'],
            'password' => $_POST['password']
        ]);
        $status = login($data['email'], $data['password'], 'email');
        if ($status) {
            header('Location: index.php');
            exit();
        }
        $error = 'Vos identifiants sont invalides.';
    }
}

includeHead();
?>
        <div class="hr"></div>
        <div id="milieu">
            <?php
            if (isset($error))
                echo "<div class='alert alert-error'><b>Erreur :</b> $error</div>";
            ?>
            <form action="" method="post">
                <label for="login">Email: </label><input type="text" name="email" placeholder="votre email"/><br />
                <label for="password">Mot de passe: </label><input type="password" name="password" placeholder="votre mot de passe"/><br />
                <input type="submit" name="submit" value="signin"/><br />
            </form>
        </div>
        <div class="hr"></div>
<?php
includeFooter();
?>