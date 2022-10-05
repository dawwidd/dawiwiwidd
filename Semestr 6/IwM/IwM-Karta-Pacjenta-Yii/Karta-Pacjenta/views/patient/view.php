<?php

use app\models\MedicationStatementSearch;
use app\models\Observation;
use app\models\ObservationSearch;
use dosamigos\datepicker\DatePicker as DatepickerDatePicker;
use yii\data\ActiveDataProvider;
use yii\db\ActiveRecord;
use yii\helpers\Html;
use yii\widgets\DetailView;
use yii\grid\GridView;
// use dosamigos\datepicker\DatePicker;
// use dosamigos\datepicker\DateRangePicker;
use kartik\daterange\DateRangePicker;

// use kartik\date\DatePicker;
// use kartik\date\DatePicker;

/* @var $this yii\web\View */
/* @var $model app\models\Patient */

$this->title = $model->name;
$this->params['breadcrumbs'][] = ['label' => 'Patients', 'url' => ['index']];
$this->params['breadcrumbs'][] = $this->title;
\yii\web\YiiAsset::register($this);
?>
<div class="patient-view">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= DetailView::widget([
        'model' => $model,
        'attributes' => [
            'id',
            'identifier:ntext',
            'name:ntext',
            'gender:ntext',
            'birthDate:ntext',
        ],
    ]) ?>

    <br>
    <br>

    <?php
    $observationSearch = new ObservationSearch();
    $dataProvider = $observationSearch->search(Yii::$app->request->get(), $model->identifier); ?>
    <?= $this->render('/observation/index', [
        'dataProvider' => $dataProvider,
        'searchModel' => $observationSearch
    ]);
    ?>

    <br>
    <br>
    <!-- <h2>Recepty tego pacjenta</h2>
    <?= GridView::widget([
        'dataProvider' => $medicationStatementDataProvider,
        'filterModel' => $medicationStatementSearch,
        'columns' => [

            'id',
            'concept:ntext',

        ],
    ]); ?> -->
    <?php
    $medicationStatementSeach = new MedicationStatementSearch();
    $dataProvider = $medicationStatementSeach->search(Yii::$app->request->get(), $model->identifier); ?>

    <?= $this->render('/medication-statement/index', [
        'dataProvider' => $dataProvider,
        'searchModel' => $medicationStatementSeach
    ]);
    ?>

</div>