<?php

use yii\helpers\Html;

/* @var $this yii\web\View */
/* @var $model app\models\Observation */

$this->title = 'Create Observation';
$this->params['breadcrumbs'][] = ['label' => 'Observations', 'url' => ['index']];
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="observation-create">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
    ]) ?>

</div>
