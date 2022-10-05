<?php

use yii\helpers\Html;
use yii\widgets\ActiveForm;

/* @var $this yii\web\View */
/* @var $model app\models\ObservationSearch */
/* @var $form yii\widgets\ActiveForm */
?>

<div class="observation-search">

    <?php $form = ActiveForm::begin([
        'action' => ['index'],
        'method' => 'get',
    ]); ?>

    <?= $form->field($model, 'id') ?>

    <?= $form->field($model, 'coding') ?>

    <?= $form->field($model, 'value') ?>

    <?= $form->field($model, 'unit') ?>

    <?= $form->field($model, 'date') ?>

    <?php // echo $form->field($model, 'patientIdentifier') ?>

    <div class="form-group">
        <?= Html::submitButton('Search', ['class' => 'btn btn-primary']) ?>
        <?= Html::resetButton('Reset', ['class' => 'btn btn-outline-secondary']) ?>
    </div>

    <?php ActiveForm::end(); ?>

</div>
