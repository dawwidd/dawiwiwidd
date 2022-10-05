<?php

use yii\helpers\Html;
use yii\widgets\ActiveForm;

/* @var $this yii\web\View */
/* @var $model app\models\Observation */
/* @var $form yii\widgets\ActiveForm */
?>

<div class="observation-form">

    <?php $form = ActiveForm::begin(); ?>

    <?= $form->field($model, 'id')->textInput() ?>

    <?= $form->field($model, 'coding')->textarea(['rows' => 6]) ?>

    <?= $form->field($model, 'value')->textInput() ?>

    <?= $form->field($model, 'unit')->textarea(['rows' => 6]) ?>

    <?= $form->field($model, 'date')->textarea(['rows' => 6]) ?>

    <?= $form->field($model, 'patientIdentifier')->textInput() ?>

    <div class="form-group">
        <?= Html::submitButton('Save', ['class' => 'btn btn-success']) ?>
    </div>

    <?php ActiveForm::end(); ?>

</div>
