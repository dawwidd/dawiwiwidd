<?php

use yii\helpers\Html;
use yii\grid\GridView;

/* @var $this yii\web\View */
/* @var $searchModel app\models\MedicationStatementSearch */
/* @var $dataProvider yii\data\ActiveDataProvider */

$this->title = 'Medication Statements';
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="medication-statement-index">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= GridView::widget([
        'dataProvider' => $dataProvider,
        'filterModel' => $searchModel,
        'columns' => [

            'id',
            'concept:ntext',
        ],
    ]); ?>


</div>