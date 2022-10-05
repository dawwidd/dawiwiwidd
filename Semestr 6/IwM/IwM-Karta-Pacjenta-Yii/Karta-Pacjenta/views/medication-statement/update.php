<?php

use yii\helpers\Html;

/* @var $this yii\web\View */
/* @var $model app\models\MedicationStatement */

$this->title = 'Update Medication Statement: ' . $model->id;
$this->params['breadcrumbs'][] = ['label' => 'Medication Statements', 'url' => ['index']];
$this->params['breadcrumbs'][] = ['label' => $model->id, 'url' => ['view', 'id' => $model->id]];
$this->params['breadcrumbs'][] = 'Update';
?>
<div class="medication-statement-update">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
    ]) ?>

</div>
