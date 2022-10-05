<?php

use yii\helpers\Html;

/* @var $this yii\web\View */
/* @var $model app\models\MedicationStatement */

$this->title = 'Create Medication Statement';
$this->params['breadcrumbs'][] = ['label' => 'Medication Statements', 'url' => ['index']];
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="medication-statement-create">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
    ]) ?>

</div>
