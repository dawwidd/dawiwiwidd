<?php

use yii\helpers\Html;
use yii\grid\GridView;
use kartik\daterange\DateRangePicker;

/* @var $this yii\web\View */
/* @var $searchModel app\models\ObservationSearch */
/* @var $dataProvider yii\data\ActiveDataProvider */

$this->title = 'Observations';
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="observation-index">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= GridView::widget([
        'dataProvider' => $dataProvider,
        'filterModel' => $searchModel,
        'columns' => [

            'coding:ntext',
            'value',
            'unit:ntext',
            [
                'value' => 'date',
                'attribute' => 'date',
                'format' => 'datetime',
                'filter' =>
                DateRangePicker::widget([
                    'model' => $searchModel,
                    // 'name' => 'datetime_range',
                    'attribute' => 'createTimeRange',
                    'convertFormat' => true,
                    // 'startAttribute' => date('Y-m-d H:i:s'),
                    // 'endAttribute' => date('Y-m-d H:i:s'),
                    'presetDropdown' => true,
                    'pluginOptions' => [
                        'timePicker' => true,
                        'timePickerIncrement' => 1,
                        'locale' => [
                            'format' => 'Y-m-d h:i:s'
                        ]
                    ]
                ])
            ],
        ],
    ]); ?>


</div>