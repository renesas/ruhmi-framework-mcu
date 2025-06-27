
# AI model compile API Specification  

## Module contents

### mera module

Mera: Public API for Mera ML compiler stack.

### mera.deploy module

Mera Deployer classes

[[mera.deploy.]{.pre}]{.sig-prename .descclassname}[[Deployer]{.pre}]{.sig-name .descname}  (#mera.deploy.Deployer "Link to this definition"){.headerlink}

:   alias of [[`MERADeployer`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}](#mera.deploy.MERADeployer "mera.deploy.MERADeployer"){.reference
    .internal}

 

*[class]{.pre}[ ]{.w}*[[mera.deploy.]{.pre}]{.sig-prename .descclassname}[[MERADeployer]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[output_dir]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}]{.n}*, *[[overwrite]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[bool]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[False]{.pre}]{.default_value}*[)]{.sig-paren}  (#mera.deploy.MERADeployer "Link to this definition"){.headerlink}

:   Bases: [`_DeployerBase`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    MERA standard deployer with MERA's compiler stack:

    [[deploy]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[model]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[MeraModel]{.pre}](#mera.mera_model.MeraModel "mera.mera_model.MeraModel"){.reference .internal}]{.n}*, *[[mera_platform]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[Platform]{.pre}](#mera.mera_platform.Platform "mera.mera_platform.Platform"){.reference .internal}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[Platform.SAKURA_2C]{.pre}]{.default_value}*, *[[build_config]{.pre}]{.n}[[=]{.pre}]{.o}[[{}]{.pre}]{.default_value}*, *[[target]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[Target]{.pre}](#mera.deploy_project.Target "mera.deploy_project.Target"){.reference .internal}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[Target.Simulator]{.pre}]{.default_value}*, *[[host_arch]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*, *[[mcu_config]{.pre}]{.n}[[=]{.pre}]{.o}[[{}]{.pre}]{.default_value}*, *[[vela_config]{.pre}]{.n}[[=]{.pre}]{.o}[[{}]{.pre}]{.default_value}*, *[[\*\*]{.pre}]{.o}[[kwargs]{.pre}]{.n}*[)]{.sig-paren}  (#mera.deploy.MERADeployer.deploy "Link to this definition"){.headerlink}

    :   Launches the compilation of a MERA project for a MERA model
        using the MERA stack.

        Parameters[:]{.colon}

        :   - **model** -- Model object loaded from mera.ModelLoader

            - **mera_platform** -- MERA platform architecture enum value

            - **build_config** -- MERA build configuration dict

            - **target** -- MERA build target

            - **host_arch** -- Host arch to deploy for. If unset, it
              will pick the current host platform, provide a value to
              override the setting.

            - **mcu_config** -- Dictionary with user overrides for MCU
              CCodegen tool. The following fields are allowed: suffix,
              weight_location, use_x86

            - **vela_config** -- Dictionary with user overrides for MCU
              Vela tool. The following fields are allowed: enable_ospi,
              config, sys_config, accel_config, optimise, memory_mode,
              verbose_all.

        Returns[:]{.colon}

        :   The object representing the result of a MERA deployment


### mera.deploy_project module  

Mera Deploy Project utilities.

*[class]{.pre}[ ]{.w}*[[mera.deploy_project.]{.pre}]{.sig-prename .descclassname}[[Layout]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[value]{.pre}]{.n}*[)]{.sig-paren}  (#mera.deploy_project.Layout "Link to this definition"){.headerlink}

:   Bases: [`Enum`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    List of possible data layouts

    [[NCHW]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'NCHW\']{.pre}*  (#mera.deploy_project.Layout.NCHW "Link to this definition"){.headerlink}

    :   N batches, Channels, Height, Width.

    [[NHWC]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'NHWC\']{.pre}*  (#mera.deploy_project.Layout.NHWC "Link to this definition"){.headerlink}

    :   N batches, Height, Width, Channels.

 

*[class]{.pre}[ ]{.w}*[[mera.deploy_project.]{.pre}]{.sig-prename .descclassname}[[Target]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[value]{.pre}]{.n}*[)]{.sig-paren}  (#mera.deploy_project.Target "Link to this definition"){.headerlink}

:   Bases: [`Enum`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    List of possible Mera Target values.

    [[IP]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'IP\',]{.pre} [False,]{.pre} [False)]{.pre}*  (#mera.deploy_project.Target.IP "Link to this definition"){.headerlink}

    :   Target HW accelerator. Valid for arm and x86 architectures.

    [[Interpreter]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'Interpreter\',]{.pre} [True,]{.pre} [True)]{.pre}*  (#mera.deploy_project.Target.Interpreter "Link to this definition"){.headerlink}

    :   Target sw interpretation of the model in floating point. Only
        valid for x86

    [[InterpreterBf16]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'InterpreterBf16\',]{.pre} [True,]{.pre} [True)]{.pre}*  (#mera.deploy_project.Target.InterpreterBf16 "Link to this definition"){.headerlink}

    :   Target sw interpretation of the model in BF16. Only valid for
        x86

    [[InterpreterHw]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'InterpreterHw\',]{.pre} [True,]{.pre} [False)]{.pre}*  (#mera.deploy_project.Target.InterpreterHw "Link to this definition"){.headerlink}

    :   Target sw interpretation of the model. Only valid for x86

    [[InterpreterHwBf16]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'InterpreterHwBf16\',]{.pre} [True,]{.pre} [True)]{.pre}*  (#mera.deploy_project.Target.InterpreterHwBf16 "Link to this definition"){.headerlink}

    :   Target IP sw interpretation of the model in BF16. Only valid for
        x86

    [[MCU]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'MCU\',]{.pre} [False,]{.pre} [True)]{.pre}*  (#mera.deploy_project.Target.MCU "Link to this definition"){.headerlink}

    :   

    [[MERA2Interpreter]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'MERAInterpreter\',]{.pre} [True,]{.pre} [True)]{.pre}*  (#mera.deploy_project.Target.MERA2Interpreter "Link to this definition"){.headerlink}

    :   

    [[MERAInterpreter]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'MERAInterpreter\',]{.pre} [True,]{.pre} [True)]{.pre}*  (#mera.deploy_project.Target.MERAInterpreter "Link to this definition"){.headerlink}

    :   

    [[Quantizer]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'Quantizer\',]{.pre} [True,]{.pre} [True)]{.pre}*  (#mera.deploy_project.Target.Quantizer "Link to this definition"){.headerlink}

    :   

    [[Simulator]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'Simulator\',]{.pre} [True,]{.pre} [False)]{.pre}*  (#mera.deploy_project.Target.Simulator "Link to this definition"){.headerlink}

    :   Target sw simulation of the IP model. Only valid for x86

    [[SimulatorBf16]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'SimulatorBf16\',]{.pre} [True,]{.pre} [True)]{.pre}*  (#mera.deploy_project.Target.SimulatorBf16 "Link to this definition"){.headerlink}

    :   Target sw simulation of the IP BF16 model. Only valid for x86

    [[VerilatorSimulator]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'VerilatorSimulator\',]{.pre} [True,]{.pre} [False)]{.pre}*  (#mera.deploy_project.Target.VerilatorSimulator "Link to this definition"){.headerlink}

    :   Target hw emulation of the IP model. Only valid for x86

 

[[mera.deploy_project.]{.pre}]{.sig-prename .descclassname}[[is_mera_project]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[path]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}]{.n}*[)]{.sig-paren} [[→]{.sig-return-icon} [[bool]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.deploy_project.is_mera_project "Link to this definition"){.headerlink}

:   Returns whether a provided path is a MeraProject or not

    Parameters[:]{.colon}

    :   **path** -- Path to check for project existence

    Returns[:]{.colon}

    :   Whether the path belongs to a project


### mera.mera_deployment module  

Mera Deployment classes

*[class]{.pre}[ ]{.w}*[[mera.mera_deployment.]{.pre}]{.sig-prename .descclassname}[[DeviceTarget]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[value]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_deployment.DeviceTarget "Link to this definition"){.headerlink}

:   Bases: [`Enum`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    List of possible MERA runtime devices for running IP deployments.

    [[INTEL_IA420]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'Intel]{.pre} [IA420\',]{.pre} [3)]{.pre}*  (#mera.mera_deployment.DeviceTarget.INTEL_IA420 "Link to this definition"){.headerlink}

    :   Target device is an Intel IA420 FPGA board.

    [[SAKURA_1]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'Sakura-1\',]{.pre} [1)]{.pre}*  (#mera.mera_deployment.DeviceTarget.SAKURA_1 "Link to this definition"){.headerlink}

    :   Target device is an EdgeCortix's Sakura-1 ASIC.

    [[SAKURA_2]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'Sakura-2\',]{.pre} [5)]{.pre}*  (#mera.mera_deployment.DeviceTarget.SAKURA_2 "Link to this definition"){.headerlink}

    :   Target device is an EdgeCortix's Sakura-2 ASIC.

    [[XILINX_U50]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'AMD]{.pre} [Xilinx]{.pre} [U50\',]{.pre} [2)]{.pre}*  (#mera.mera_deployment.DeviceTarget.XILINX_U50 "Link to this definition"){.headerlink}

    :   Target device is an AMD Xilinx U50 FPGA board.

    *[property]{.pre}[ ]{.w}*[[code]{.pre}]{.sig-name .descname}  (#mera.mera_deployment.DeviceTarget.code "Link to this definition"){.headerlink}

    :   


*[class]{.pre}[ ]{.w}*[[mera.mera_deployment.]{.pre}]{.sig-prename .descclassname}[[MeraDeployment]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[plan_loc]{.pre}]{.n}*, *[[target]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_deployment.MeraDeployment "Link to this definition"){.headerlink}

:   Bases: [`object`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    [[get_runner]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[device_target]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[DeviceTarget]{.pre}](#mera.mera_deployment.DeviceTarget "mera.mera_deployment.DeviceTarget"){.reference .internal}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[DeviceTarget.SAKURA_1]{.pre}]{.default_value}*, *[[device_ids]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[List]{.pre}[[\[]{.pre}]{.p}[int]{.pre}[[\]]{.pre}]{.p}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*, *[[dynamic_output_list]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[List]{.pre}[[\[]{.pre}]{.p}[str]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[int]{.pre}[[\]]{.pre}]{.p}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*[)]{.sig-paren} [[→]{.sig-return-icon} [[[MeraModelRunner]{.pre}](#mera.mera_deployment.MeraModelRunner "mera.mera_deployment.MeraModelRunner"){.reference .internal}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraDeployment.get_runner "Link to this definition"){.headerlink}

    :   Prepares the model for running with a given target

        Parameters[:]{.colon}

        :   - **device_target** -- Selects the device run target where
              the IP deployment will be run. Only applicable for
              deployments with target=IP. See DeviceTarget enum for a
              detailed list of possible values.

            - **device_ids** -- When running in a multi card
              environment, selects the SAKURA device(s) where the
              deployment will be run. If unset, MERA will automatically
              select any available card in the system. Only applicable
              in the case device_target=DeviceTarget.SAKURA_1

            - **dynamic_output_list** -- Marks certain outputs so that
              only a dynamic subset of the data is returned. See special
              get_output_row() function in MeraModelRunner. This feature
              is only supported when running in IP.

        Returns[:]{.colon}

        :   Runner object

 

*[class]{.pre}[ ]{.w}*[[mera.mera_deployment.]{.pre}]{.sig-prename .descclassname}[[MeraInterpreterDeployment]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[model_loc]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_deployment.MeraInterpreterDeployment "Link to this definition"){.headerlink}

:   Bases: [`object`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    [[get_runner]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[profiling_mode]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[bool]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[False]{.pre}]{.default_value}*, *[[config_dict]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[Dict]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[{}]{.pre}]{.default_value}*, *[[\*\*]{.pre}]{.o}[[kwargs]{.pre}]{.n}*[)]{.sig-paren} [[→]{.sig-return-icon} [[[MeraInterpreterModelRunner]{.pre}](#mera.mera_deployment.MeraInterpreterModelRunner "mera.mera_deployment.MeraInterpreterModelRunner"){.reference .internal}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraInterpreterDeployment.get_runner "Link to this definition"){.headerlink}

    :   Prepares the Interpreter for running the model.

        Parameters[:]{.colon}

        :   **profiling_mode** -- Enables collection of node execution
            times.

        Returns[:]{.colon}

        :   Runner object

 

*[class]{.pre}[ ]{.w}*[[mera.mera_deployment.]{.pre}]{.sig-prename .descclassname}[[MeraInterpreterModelRunner]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[int_runner]{.pre}]{.n}*, *[[int_cfg]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_deployment.MeraInterpreterModelRunner "Link to this definition"){.headerlink}

:   Bases: [[`ModelRunnerBase`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}](#mera.mera_deployment.ModelRunnerBase "mera.mera_deployment.ModelRunnerBase"){.reference
    .internal}

    [[display_profiling_table]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren}  (#mera.mera_deployment.MeraInterpreterModelRunner.display_profiling_table "Link to this definition"){.headerlink}

    :   

    [[get_num_inputs]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[int]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraInterpreterModelRunner.get_num_inputs "Link to this definition"){.headerlink}

    :   

    [[get_num_outputs]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[int]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraInterpreterModelRunner.get_num_outputs "Link to this definition"){.headerlink}

    :   Gets the number of available outputs

        Returns[:]{.colon}

        :   Number of output variables

    [[get_output]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[output_idx]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[0]{.pre}]{.default_value}*[)]{.sig-paren} [[→]{.sig-return-icon} [[ndarray]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraInterpreterModelRunner.get_output "Link to this definition"){.headerlink}

    :   Returns the output tensor given an output id index.
        [[`run()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraInterpreterModelRunner.run "mera.mera_deployment.MeraInterpreterModelRunner.run"){.reference
        .internal} needs to be called before [[`get_output()`{.xref .py
        .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraInterpreterModelRunner.get_output "mera.mera_deployment.MeraInterpreterModelRunner.get_output"){.reference
        .internal}

        Parameters[:]{.colon}

        :   **output_idx** -- Index of output variable to query

        Returns[:]{.colon}

        :   Output tensor values in numpy format

    [[get_output_row]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[row_idx]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}]{.n}*, *[[output_idx]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[0]{.pre}]{.default_value}*[)]{.sig-paren} [[→]{.sig-return-icon} [[ndarray]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraInterpreterModelRunner.get_output_row "Link to this definition"){.headerlink}

    :   

    [[get_outputs]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[List]{.pre}[[\[]{.pre}]{.p}[ndarray]{.pre}[[\]]{.pre}]{.p}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraInterpreterModelRunner.get_outputs "Link to this definition"){.headerlink}

    :   Returns a list of all output tensors. Equivalent to
        [[`get_output()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraInterpreterModelRunner.get_output "mera.mera_deployment.MeraInterpreterModelRunner.get_output"){.reference
        .internal} from \[0, get_num_outputs()\]

        Returns[:]{.colon}

        :   List of output tensor values in numpy format

    [[get_outputs_dict]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[Dict]{.pre}[[\[]{.pre}]{.p}[str]{.pre}[[,]{.pre}]{.p}[ ]{.w}[ndarray]{.pre}[[\]]{.pre}]{.p}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraInterpreterModelRunner.get_outputs_dict "Link to this definition"){.headerlink}

    :   

    [[get_power_metrics]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[PowerMetrics]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraInterpreterModelRunner.get_power_metrics "Link to this definition"){.headerlink}

    :   Gets the power metrics reported from MERA after a
        [[`run()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraInterpreterModelRunner.run "mera.mera_deployment.MeraInterpreterModelRunner.run"){.reference
        .internal}. Note power measurement mode might need to be enable
        in order to collect and generate such metrics.

        Returns[:]{.colon}

        :   Container with summary analysis of all collected metrics
            from MERA.

    [[get_runtime_metrics]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[dict]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraInterpreterModelRunner.get_runtime_metrics "Link to this definition"){.headerlink}

    :   Gets the runtime metrics reported from Mera after a
        [[`run()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraInterpreterModelRunner.run "mera.mera_deployment.MeraInterpreterModelRunner.run"){.reference
        .internal}

        Returns[:]{.colon}

        :   Dictionary of measured metrics

    [[run]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[None]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraInterpreterModelRunner.run "Link to this definition"){.headerlink}

    :   Runs the model with the specified input data.
        [[`set_input()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraInterpreterModelRunner.set_input "mera.mera_deployment.MeraInterpreterModelRunner.set_input"){.reference
        .internal} needs to be called before [[`run()`{.xref .py
        .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraInterpreterModelRunner.run "mera.mera_deployment.MeraInterpreterModelRunner.run"){.reference
        .internal}

    [[set_input]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[data]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[Dict]{.pre}[[\[]{.pre}]{.p}[str]{.pre}[[,]{.pre}]{.p}[ ]{.w}[ndarray]{.pre}[[\]]{.pre}]{.p}]{.n}*[)]{.sig-paren}  (#mera.mera_deployment.MeraInterpreterModelRunner.set_input "Link to this definition"){.headerlink}

    :   Sets the input data for running

        Parameters[:]{.colon}

        :   **data** -- Input numpy data tensor or dict of input numpy
            data tensors if the model has more than one input. Setting
            multiple inputs should have the format {input_name :
            input_data}

 

*[class]{.pre}[ ]{.w}*[[mera.mera_deployment.]{.pre}]{.sig-prename .descclassname}[[MeraInterpreterPrjDeployment]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[model_loc]{.pre}]{.n}*, *[[prj]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_deployment.MeraInterpreterPrjDeployment "Link to this definition"){.headerlink}

:   Bases: [[`MeraInterpreterDeployment`{.xref .py .py-class .docutils
    .literal
    .notranslate}]{.pre}](#mera.mera_deployment.MeraInterpreterDeployment "mera.mera_deployment.MeraInterpreterDeployment"){.reference
    .internal}

 

*[class]{.pre}[ ]{.w}*[[mera.mera_deployment.]{.pre}]{.sig-prename .descclassname}[[MeraModelRunner]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[runner]{.pre}]{.n}*, *[[plan]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_deployment.MeraModelRunner "Link to this definition"){.headerlink}

:   Bases: [[`ModelRunnerBase`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}](#mera.mera_deployment.ModelRunnerBase "mera.mera_deployment.ModelRunnerBase"){.reference
    .internal}

    [[get_input_handle]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[name]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}]{.n}*, *[[as_numpy]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[bool]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[True]{.pre}]{.default_value}*, *[[dtype]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[\'float32\']{.pre}]{.default_value}*[)]{.sig-paren}  (#mera.mera_deployment.MeraModelRunner.get_input_handle "Link to this definition"){.headerlink}

    :   Gets the zero-copy handler to the specified model input. :param
        name: Name of the input. :param as_numpy: Whether to prepare
        handle as numpy array. Defaults to true. :param dtype: Viewer
        data type.

        Returns[:]{.colon}

        :   Input data handler.

    [[get_input_names]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[List]{.pre}[[\[]{.pre}]{.p}[str]{.pre}[[\]]{.pre}]{.p}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraModelRunner.get_input_names "Link to this definition"){.headerlink}

    :   

    [[get_num_outputs]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[int]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraModelRunner.get_num_outputs "Link to this definition"){.headerlink}

    :   Gets the number of available outputs

        Returns[:]{.colon}

        :   Number of output variables

    [[get_output]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[output_idx]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[0]{.pre}]{.default_value}*[)]{.sig-paren} [[→]{.sig-return-icon} [[ndarray]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraModelRunner.get_output "Link to this definition"){.headerlink}

    :   Returns the output tensor given an output id index.
        [[`run()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraModelRunner.run "mera.mera_deployment.MeraModelRunner.run"){.reference
        .internal} needs to be called before [[`get_output()`{.xref .py
        .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraModelRunner.get_output "mera.mera_deployment.MeraModelRunner.get_output"){.reference
        .internal}

        Parameters[:]{.colon}

        :   **output_idx** -- Index of output variable to query

        Returns[:]{.colon}

        :   Output tensor values in numpy format

    [[get_output_handle]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[name]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}]{.n}*, *[[as_numpy]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[bool]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[True]{.pre}]{.default_value}*, *[[dtype]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[\'float32\']{.pre}]{.default_value}*[)]{.sig-paren}  (#mera.mera_deployment.MeraModelRunner.get_output_handle "Link to this definition"){.headerlink}

    :   Gets the zero-copy handler to the specified model output. :param
        name: Name of the output. :param as_numpy: Whether to prepare
        handle as numpy array. Defaults to true. :param dtype: Viewer
        data type.

        Returns[:]{.colon}

        :   Output data handler.

    [[get_output_names]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[List]{.pre}[[\[]{.pre}]{.p}[str]{.pre}[[\]]{.pre}]{.p}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraModelRunner.get_output_names "Link to this definition"){.headerlink}

    :   

    [[get_output_row]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[row_idx]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}]{.n}*, *[[output_idx]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[0]{.pre}]{.default_value}*[)]{.sig-paren} [[→]{.sig-return-icon} [[ndarray]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraModelRunner.get_output_row "Link to this definition"){.headerlink}

    :   

    [[get_outputs]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[List]{.pre}[[\[]{.pre}]{.p}[ndarray]{.pre}[[\]]{.pre}]{.p}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraModelRunner.get_outputs "Link to this definition"){.headerlink}

    :   Returns a list of all output tensors. Equivalent to
        [[`get_output()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraModelRunner.get_output "mera.mera_deployment.MeraModelRunner.get_output"){.reference
        .internal} from \[0, get_num_outputs()\]

        Returns[:]{.colon}

        :   List of output tensor values in numpy format

    [[get_outputs_dict]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[Dict]{.pre}[[\[]{.pre}]{.p}[str]{.pre}[[,]{.pre}]{.p}[ ]{.w}[ndarray]{.pre}[[\]]{.pre}]{.p}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraModelRunner.get_outputs_dict "Link to this definition"){.headerlink}

    :   

    [[get_power_metrics]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[PowerMetrics]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraModelRunner.get_power_metrics "Link to this definition"){.headerlink}

    :   Gets the power metrics reported from MERA after a
        [[`run()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraModelRunner.run "mera.mera_deployment.MeraModelRunner.run"){.reference
        .internal}. Note power measurement mode might need to be enable
        in order to collect and generate such metrics.

        Returns[:]{.colon}

        :   Container with summary analysis of all collected metrics
            from MERA.

    [[get_runtime_metrics]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[dict]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraModelRunner.get_runtime_metrics "Link to this definition"){.headerlink}

    :   Gets the runtime metrics reported from Mera after a
        [[`run()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraModelRunner.run "mera.mera_deployment.MeraModelRunner.run"){.reference
        .internal}

        Returns[:]{.colon}

        :   Dictionary of measured metrics

    [[run]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[None]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraModelRunner.run "Link to this definition"){.headerlink}

    :   Runs the model with the specified input data.
        [[`set_input()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraModelRunner.set_input "mera.mera_deployment.MeraModelRunner.set_input"){.reference
        .internal} needs to be called before [[`run()`{.xref .py
        .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraModelRunner.run "mera.mera_deployment.MeraModelRunner.run"){.reference
        .internal}

    [[set_input]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[data]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[ndarray]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[Dict]{.pre}[[\[]{.pre}]{.p}[str]{.pre}[[,]{.pre}]{.p}[ ]{.w}[ndarray]{.pre}[[\]]{.pre}]{.p}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[List]{.pre}[[\[]{.pre}]{.p}[ndarray]{.pre}[[\]]{.pre}]{.p}]{.n}*[)]{.sig-paren}  (#mera.mera_deployment.MeraModelRunner.set_input "Link to this definition"){.headerlink}

    :   Sets the input data for running

        Parameters[:]{.colon}

        :   **data** -- Input numpy data tensor or dict of input numpy
            data tensors if the model has more than one input. Setting
            multiple inputs should have the format {input_name :
            input_data}

    [[set_named_input]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[name]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}]{.n}*, *[[data]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[ndarray]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_deployment.MeraModelRunner.set_named_input "Link to this definition"){.headerlink}

    :   Gets the zero-copy numpy handler and copies data to the device.
        :param name: Name of the input.

 

*[class]{.pre}[ ]{.w}*[[mera.mera_deployment.]{.pre}]{.sig-prename .descclassname}[[MeraPrjDeployment]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[plan_loc]{.pre}]{.n}*, *[[prj]{.pre}]{.n}*, *[[target]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_deployment.MeraPrjDeployment "Link to this definition"){.headerlink}

:   Bases: [[`MeraDeployment`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}](#mera.mera_deployment.MeraDeployment "mera.mera_deployment.MeraDeployment"){.reference
    .internal}

 

*[class]{.pre}[ ]{.w}*[[mera.mera_deployment.]{.pre}]{.sig-prename .descclassname}[[MeraTvmModelRunner]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[rt_mod]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_deployment.MeraTvmModelRunner "Link to this definition"){.headerlink}

:   Bases: [[`ModelRunnerBase`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}](#mera.mera_deployment.ModelRunnerBase "mera.mera_deployment.ModelRunnerBase"){.reference
    .internal}

    [[get_num_outputs]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[int]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraTvmModelRunner.get_num_outputs "Link to this definition"){.headerlink}

    :   Gets the number of available outputs

        Returns[:]{.colon}

        :   Number of output variables

    [[get_output]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[output_idx]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[0]{.pre}]{.default_value}*[)]{.sig-paren} [[→]{.sig-return-icon} [[ndarray]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraTvmModelRunner.get_output "Link to this definition"){.headerlink}

    :   Returns the output tensor given an output id index.
        [[`run()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraTvmModelRunner.run "mera.mera_deployment.MeraTvmModelRunner.run"){.reference
        .internal} needs to be called before [[`get_output()`{.xref .py
        .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraTvmModelRunner.get_output "mera.mera_deployment.MeraTvmModelRunner.get_output"){.reference
        .internal}

        Parameters[:]{.colon}

        :   **output_idx** -- Index of output variable to query

        Returns[:]{.colon}

        :   Output tensor values in numpy format

    [[get_outputs]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[List]{.pre}[[\[]{.pre}]{.p}[ndarray]{.pre}[[\]]{.pre}]{.p}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraTvmModelRunner.get_outputs "Link to this definition"){.headerlink}

    :   Returns a list of all output tensors. Equivalent to
        [[`get_output()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraTvmModelRunner.get_output "mera.mera_deployment.MeraTvmModelRunner.get_output"){.reference
        .internal} from \[0, get_num_outputs()\]

        Returns[:]{.colon}

        :   List of output tensor values in numpy format

    [[get_power_metrics]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[PowerMetrics]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraTvmModelRunner.get_power_metrics "Link to this definition"){.headerlink}

    :   Gets the power metrics reported from MERA after a
        [[`run()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraTvmModelRunner.run "mera.mera_deployment.MeraTvmModelRunner.run"){.reference
        .internal}. Note power measurement mode might need to be enable
        in order to collect and generate such metrics.

        Returns[:]{.colon}

        :   Container with summary analysis of all collected metrics
            from MERA.

    [[get_runtime_metrics]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[dict]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraTvmModelRunner.get_runtime_metrics "Link to this definition"){.headerlink}

    :   Gets the runtime metrics reported from Mera after a
        [[`run()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraTvmModelRunner.run "mera.mera_deployment.MeraTvmModelRunner.run"){.reference
        .internal}

        Returns[:]{.colon}

        :   Dictionary of measured metrics

    [[run]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[None]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.MeraTvmModelRunner.run "Link to this definition"){.headerlink}

    :   Runs the model with the specified input data.
        [[`set_input()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraTvmModelRunner.set_input "mera.mera_deployment.MeraTvmModelRunner.set_input"){.reference
        .internal} needs to be called before [[`run()`{.xref .py
        .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.MeraTvmModelRunner.run "mera.mera_deployment.MeraTvmModelRunner.run"){.reference
        .internal}

    [[set_input]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[data]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[ndarray]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[Dict]{.pre}[[\[]{.pre}]{.p}[str]{.pre}[[,]{.pre}]{.p}[ ]{.w}[ndarray]{.pre}[[\]]{.pre}]{.p}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[List]{.pre}[[\[]{.pre}]{.p}[ndarray]{.pre}[[\]]{.pre}]{.p}]{.n}*[)]{.sig-paren}  (#mera.mera_deployment.MeraTvmModelRunner.set_input "Link to this definition"){.headerlink}

    :   Sets the input data for running

        Parameters[:]{.colon}

        :   **data** -- Input numpy data tensor or dict of input numpy
            data tensors if the model has more than one input. Setting
            multiple inputs should have the format {input_name :
            input_data}

 

*[class]{.pre}[ ]{.w}*[[mera.mera_deployment.]{.pre}]{.sig-prename .descclassname}[[ModelRunnerBase]{.pre}]{.sig-name .descname}  (#mera.mera_deployment.ModelRunnerBase "Link to this definition"){.headerlink}

:   Bases: [`object`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    API for runtime inference of a model.

    *[abstract]{.pre}[ ]{.w}*[[get_num_outputs]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[int]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.ModelRunnerBase.get_num_outputs "Link to this definition"){.headerlink}

    :   Gets the number of available outputs

        Returns[:]{.colon}

        :   Number of output variables

    *[abstract]{.pre}[ ]{.w}*[[get_output]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[output_idx]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[0]{.pre}]{.default_value}*[)]{.sig-paren} [[→]{.sig-return-icon} [[ndarray]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.ModelRunnerBase.get_output "Link to this definition"){.headerlink}

    :   Returns the output tensor given an output id index.
        [[`run()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.ModelRunnerBase.run "mera.mera_deployment.ModelRunnerBase.run"){.reference
        .internal} needs to be called before [[`get_output()`{.xref .py
        .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.ModelRunnerBase.get_output "mera.mera_deployment.ModelRunnerBase.get_output"){.reference
        .internal}

        Parameters[:]{.colon}

        :   **output_idx** -- Index of output variable to query

        Returns[:]{.colon}

        :   Output tensor values in numpy format

    *[abstract]{.pre}[ ]{.w}*[[get_outputs]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[List]{.pre}[[\[]{.pre}]{.p}[ndarray]{.pre}[[\]]{.pre}]{.p}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.ModelRunnerBase.get_outputs "Link to this definition"){.headerlink}

    :   Returns a list of all output tensors. Equivalent to
        [[`get_output()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.ModelRunnerBase.get_output "mera.mera_deployment.ModelRunnerBase.get_output"){.reference
        .internal} from \[0, get_num_outputs()\]

        Returns[:]{.colon}

        :   List of output tensor values in numpy format

    *[abstract]{.pre}[ ]{.w}*[[get_power_metrics]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[PowerMetrics]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.ModelRunnerBase.get_power_metrics "Link to this definition"){.headerlink}

    :   Gets the power metrics reported from MERA after a
        [[`run()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.ModelRunnerBase.run "mera.mera_deployment.ModelRunnerBase.run"){.reference
        .internal}. Note power measurement mode might need to be enable
        in order to collect and generate such metrics.

        Returns[:]{.colon}

        :   Container with summary analysis of all collected metrics
            from MERA.

    *[abstract]{.pre}[ ]{.w}*[[get_runtime_metrics]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[dict]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.ModelRunnerBase.get_runtime_metrics "Link to this definition"){.headerlink}

    :   Gets the runtime metrics reported from Mera after a
        [[`run()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.ModelRunnerBase.run "mera.mera_deployment.ModelRunnerBase.run"){.reference
        .internal}

        Returns[:]{.colon}

        :   Dictionary of measured metrics

    *[abstract]{.pre}[ ]{.w}*[[run]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[None]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_deployment.ModelRunnerBase.run "Link to this definition"){.headerlink}

    :   Runs the model with the specified input data.
        [[`set_input()`{.xref .py .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.ModelRunnerBase.set_input "mera.mera_deployment.ModelRunnerBase.set_input"){.reference
        .internal} needs to be called before [[`run()`{.xref .py
        .py-func .docutils .literal
        .notranslate}]{.pre}](#mera.mera_deployment.ModelRunnerBase.run "mera.mera_deployment.ModelRunnerBase.run"){.reference
        .internal}

    *[abstract]{.pre}[ ]{.w}*[[set_input]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[data]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[ndarray]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[Dict]{.pre}[[\[]{.pre}]{.p}[str]{.pre}[[,]{.pre}]{.p}[ ]{.w}[ndarray]{.pre}[[\]]{.pre}]{.p}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[List]{.pre}[[\[]{.pre}]{.p}[ndarray]{.pre}[[\]]{.pre}]{.p}]{.n}*[)]{.sig-paren}  (#mera.mera_deployment.ModelRunnerBase.set_input "Link to this definition"){.headerlink}

    :   Sets the input data for running

        Parameters[:]{.colon}

        :   **data** -- Input numpy data tensor or dict of input numpy
            data tensors if the model has more than one input. Setting
            multiple inputs should have the format {input_name :
            input_data}

 

[[mera.mera_deployment.]{.pre}]{.sig-prename .descclassname}[[load_mera_deployment]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[path]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}]{.n}*, *[[target]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[Target]{.pre}](#mera.deploy_project.Target "mera.deploy_project.Target"){.reference .internal}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*[)]{.sig-paren}  (#mera.mera_deployment.load_mera_deployment "Link to this definition"){.headerlink}

:   Loads an already built deployment from a directory

    Parameters[:]{.colon}

    :   - **path** -- Directory of a Mera deployment project or full
          directory of built mera results

        - **target** -- If there are multiple targets built in the mera
          project selects which one. Optional if not loading a project
          or if there is a single target built.

    Returns[:]{.colon}

    :   Reference to deployment object

### mera.mera_model module  

Mera Model classes.

*[class]{.pre}[ ]{.w}*[[mera.mera_model.]{.pre}]{.sig-prename .descclassname}[[Mera2ModelQuantized]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[prj]{.pre}]{.n}*, *[[model_name]{.pre}]{.n}*, *[[model_path]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_model.Mera2ModelQuantized "Link to this definition"){.headerlink}

:   Bases: [[`MeraModel`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}](#mera.mera_model.MeraModel "mera.mera_model.MeraModel"){.reference
    .internal}

    MeraModel class of a model quantized with MERA2 tools.

 

*[class]{.pre}[ ]{.w}*[[mera.mera_model.]{.pre}]{.sig-prename .descclassname}[[MeraModel]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[prj]{.pre}]{.n}*, *[[model_name]{.pre}]{.n}*, *[[model_path]{.pre}]{.n}*, *[[use_prequantize_input]{.pre}]{.n}[[=]{.pre}]{.o}[[False]{.pre}]{.default_value}*, *[[save_model]{.pre}]{.n}[[=]{.pre}]{.o}[[False]{.pre}]{.default_value}*[)]{.sig-paren}  (#mera.mera_model.MeraModel "Link to this definition"){.headerlink}

:   Bases: [`object`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    Base class representing a ML model compatible with MERA deployment
    project.

    [[get_input_shape]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[input_name]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*[)]{.sig-paren} [[→]{.sig-return-icon} [[Tuple]{.pre}[[\[]{.pre}]{.p}[int]{.pre}[[\]]{.pre}]{.p}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_model.MeraModel.get_input_shape "Link to this definition"){.headerlink}

    :   Utility class to query the shape of an input variable of the
        model

        Parameters[:]{.colon}

        :   **input_name** -- Specifies which input to get the shape
            from. If unset, assumes there is only one input.

        Returns[:]{.colon}

        :   A tuple with 4 items representing the shape of the input
            variable in the model.

    *[property]{.pre}[ ]{.w}*[[input_desc]{.pre}]{.sig-name .descname}  (#mera.mera_model.MeraModel.input_desc "Link to this definition"){.headerlink}

    :   

 

*[class]{.pre}[ ]{.w}*[[mera.mera_model.]{.pre}]{.sig-prename .descclassname}[[MeraModelExecutorch]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[prj]{.pre}]{.n}*, *[[model_name]{.pre}]{.n}*, *[[model_path]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_model.MeraModelExecutorch "Link to this definition"){.headerlink}

:   Bases: [[`MeraModel`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}](#mera.mera_model.MeraModel "mera.mera_model.MeraModel"){.reference
    .internal}

    Specialization of MeraModel for a Executorch/EXIR ML model.

 

*[class]{.pre}[ ]{.w}*[[mera.mera_model.]{.pre}]{.sig-prename .descclassname}[[MeraModelOnnx]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[prj]{.pre}]{.n}*, *[[model_name]{.pre}]{.n}*, *[[model_path]{.pre}]{.n}*, *[[batch_num]{.pre}]{.n}*, *[[shape_mapping]{.pre}]{.n}*, *[[model_info]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_model.MeraModelOnnx "Link to this definition"){.headerlink}

:   Bases: [[`MeraModel`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}](#mera.mera_model.MeraModel "mera.mera_model.MeraModel"){.reference
    .internal}

    Specialization of MeraModel for a ONNX ML model.

 

*[class]{.pre}[ ]{.w}*[[mera.mera_model.]{.pre}]{.sig-prename .descclassname}[[MeraModelTflite]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[prj]{.pre}]{.n}*, *[[model_name]{.pre}]{.n}*, *[[model_path]{.pre}]{.n}*, *[[use_prequantize_input]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_model.MeraModelTflite "Link to this definition"){.headerlink}

:   Bases: [[`MeraModel`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}](#mera.mera_model.MeraModel "mera.mera_model.MeraModel"){.reference
    .internal}

    Specialization of MeraModel for a TFLite ML model.

 

*[class]{.pre}[ ]{.w}*[[mera.mera_model.]{.pre}]{.sig-prename .descclassname}[[ModelLoader]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[deployer]{.pre}]{.n}[[=]{.pre}]{.o}[[None]{.pre}]{.default_value}*[)]{.sig-paren}  (#mera.mera_model.ModelLoader "Link to this definition"){.headerlink}

:   Bases: [`object`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    Utility class for loading and converting ML models into models
    compatible with MERA

    Parameters[:]{.colon}

    :   **deployer** (*mera.deploy.TVMDeployer*) -- Reference to a MERA
        deployer class, if None is provided, information about the model
        will not be added to the deployment project.

    [[from_executorch]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[model_path]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}]{.n}*, *[[model_name]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*[)]{.sig-paren} [[→]{.sig-return-icon} [[[MeraModelExecutorch]{.pre}](#mera.mera_model.MeraModelExecutorch "mera.mera_model.MeraModelExecutorch"){.reference .internal}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_model.ModelLoader.from_executorch "Link to this definition"){.headerlink}

    :   Converts a PyTorch model in Executorch/EXIR format (.pte) into a
        compatible model for MERA.

        Parameters[:]{.colon}

        :   - **model_path** -- Path to the PyTorch model file in
              ExecuTorch format (.pte)

            - **model_name** -- Display name of the model being
              deployed. Will default to the stem name of the model file
              if not provided.

        Returns[:]{.colon}

        :   The input model compatible with MERA.

    [[from_onnx]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[model_path]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}]{.n}*, *[[model_name]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*, *[[layout]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[Layout]{.pre}](#mera.deploy_project.Layout "mera.deploy_project.Layout"){.reference .internal}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[Layout.NHWC]{.pre}]{.default_value}*, *[[batch_num]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[1]{.pre}]{.default_value}*, *[[shape_mapping]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[Dict]{.pre}[[\[]{.pre}]{.p}[str]{.pre}[[,]{.pre}]{.p}[ ]{.w}[int]{.pre}[[\]]{.pre}]{.p}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[{}]{.pre}]{.default_value}*, *[[model_info]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[Dict]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[{}]{.pre}]{.default_value}*[)]{.sig-paren} [[→]{.sig-return-icon} [[[MeraModelOnnx]{.pre}](#mera.mera_model.MeraModelOnnx "mera.mera_model.MeraModelOnnx"){.reference .internal}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_model.ModelLoader.from_onnx "Link to this definition"){.headerlink}

    :   Converts a ONNX model into a compatible model for MERA. NOTE
        this loader is best optimised for float models using op_set=12

        Parameters[:]{.colon}

        :   - **model_path** -- Path to the ONNX model file.

            - **model_name** -- Display name of the model being
              deployed. Will default to the stem name of the model file
              if not provided.

            - **layout** -- Data layout of the model being loaded.
              Defaults to NHWC layout

            - **batch_num** -- If the model contains symbolic batch
              numbers, loads it resolving its value to the parameter
              provided. Defaults to 1.

            - **shape_mapping** -- If the model contains symbolic
              shapes, provides their static mapping.

            - **model_info** -- An optional dictionary with model's
              metadata or other hyperparameters.

        Returns[:]{.colon}

        :   The input model compatible with MERA.

    [[from_pytorch]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[model_path]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}]{.n}*, *[[input_desc]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[Dict]{.pre}[[\[]{.pre}]{.p}[str]{.pre}[[,]{.pre}]{.p}[ ]{.w}[tuple]{.pre}[[\]]{.pre}]{.p}]{.n}*, *[[model_name]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*, *[[layout]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[Layout]{.pre}](#mera.deploy_project.Layout "mera.deploy_project.Layout"){.reference .internal}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[Layout.NHWC]{.pre}]{.default_value}*, *[[use_prequantize_input]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[bool]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[False]{.pre}]{.default_value}*[)]{.sig-paren} [[→]{.sig-return-icon} [[MeraModelPytorch]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_model.ModelLoader.from_pytorch "Link to this definition"){.headerlink}

    :   \<\<Deprecated\>\> Converts a PyTorch model in TorchScript
        format into a compatible model for MERA.

        Parameters[:]{.colon}

        :   - **model_path** -- Path to the PyTorch model file in
              TorchScript format

            - **input_desc** -- Map of input names and their dimensions
              and types. Expects a format of {input_name : (input_size,
              input_type)}

            - **model_name** -- Display name of the model being
              deployed. Will default to the stem name of the model file
              if not provided.

            - **layout** -- Data layout of the model being loaded.
              Defaults to NHWC layout

            - **use_prequantize_input** -- Whether input is provided
              prequantized, or not. Defaults to False

        Returns[:]{.colon}

        :   The input model compatible with MERA.

    [[from_quantized_mera]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[model_path]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}]{.n}*, *[[model_name]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*, *[[use_legacy]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[bool]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[False]{.pre}]{.default_value}*[)]{.sig-paren}  (#mera.mera_model.ModelLoader.from_quantized_mera "Link to this definition"){.headerlink}

    :   Converts a previously quantized MERA model into a compatible
        deployable model.

        Parameters[:]{.colon}

        :   - **model_path** -- Path to the MERA model file

            - **model_name** -- Display name of the model being
              deployed. Will default to the stem name of the model file
              if not provided.

            - **use_legacy** -- Whether to use older MERA v1 model
              loader. Use only in the case of legacy quantizer.

        Returns[:]{.colon}

        :   The input model compatible with MERA.

    [[from_tflite]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[model_path]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}]{.n}*, *[[model_name]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[str]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*, *[[use_prequantize_input]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[bool]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[False]{.pre}]{.default_value}*[)]{.sig-paren} [[→]{.sig-return-icon} [[[MeraModelTflite]{.pre}](#mera.mera_model.MeraModelTflite "mera.mera_model.MeraModelTflite"){.reference .internal}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_model.ModelLoader.from_tflite "Link to this definition"){.headerlink}

    :   Converts a tensorflow model in TFLite format into a compatible
        model for MERA.

        Parameters[:]{.colon}

        :   - **model_path** -- Path to the tensorflow model file in
              TFLite format

            - **model_name** -- Display name of the model being
              deployed. Will default to the stem name of the model file
              if not provided.

            - **use_prequantize_input** -- Whether input is provided
              prequantized, or not. Defaults to False

        Returns[:]{.colon}

        :   The input model compatible with MERA.

    [[fuse_models]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[mera_models]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[Tuple]{.pre}[[\[]{.pre}]{.p}[[MeraModel]{.pre}](#mera.mera_model.MeraModel "mera.mera_model.MeraModel"){.reference .internal}[[\]]{.pre}]{.p}]{.n}*, *[[share_input]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[bool]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[False]{.pre}]{.default_value}*[)]{.sig-paren} [[→]{.sig-return-icon} [[MeraModelFused]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_model.ModelLoader.fuse_models "Link to this definition"){.headerlink}

    :   

        Fusing multiple MERA models into a single model for compilation and deployment.

        :   This is especially useful for fully utilizing the compute
            resources of a large platform. The inputs of the fused model
            are the concatenation of the inputs of the models to be
            fused. Similarly, the outputs of the fused model are the
            concatenation of the outputs of the models to be fused. For
            example, let's suppose mera_models has two models, m1 and
            m2, then for the fused model, the inputs are \[m1 inputs, m2
            inputs\] and the outputs are \[m1 outputs, m2 outputs\].
            When each model in mera_models has one input and share_input
            is True, the fused model has one input.

        Parameters[:]{.colon}

        :   - **mera_models** -- List of MERA models to be fused.

            - **share_input** -- Whether the models share input or not.

        Returns[:]{.colon}

        :   The fused model.


### mera.mera_platform module  

MERA platform selection

*[class]{.pre}[ ]{.w}*[[mera.mera_platform.]{.pre}]{.sig-prename .descclassname}[[AccelKind]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[value]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_platform.AccelKind "Link to this definition"){.headerlink}

:   Bases: [`Enum`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    An enumeration.

    [[CPU]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'CPU\']{.pre}*  (#mera.mera_platform.AccelKind.CPU "Link to this definition"){.headerlink}

    :   

    [[DNA]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNA\']{.pre}*  (#mera.mera_platform.AccelKind.DNA "Link to this definition"){.headerlink}

    :   

    [[GPU]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'GPU\']{.pre}*  (#mera.mera_platform.AccelKind.GPU "Link to this definition"){.headerlink}

    :   

    [[MCU]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'MCU\']{.pre}*  (#mera.mera_platform.AccelKind.MCU "Link to this definition"){.headerlink}

    :   

 

*[class]{.pre}[ ]{.w}*[[mera.mera_platform.]{.pre}]{.sig-prename .descclassname}[[Platform]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[value]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_platform.Platform "Link to this definition"){.headerlink}

:   Bases: [`Enum`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    List of all valid MERA platforms

    [[ALT1]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'ALT1\',]{.pre} [AccelKind.MCU)]{.pre}*  (#mera.mera_platform.Platform.ALT1 "Link to this definition"){.headerlink}

    :   

    [[ALT2]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'ALT2\',]{.pre} [AccelKind.MCU)]{.pre}*  (#mera.mera_platform.Platform.ALT2 "Link to this definition"){.headerlink}

    :   

    [[DNAA400L0001]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAA400L0001\']{.pre}*  (#mera.mera_platform.Platform.DNAA400L0001 "Link to this definition"){.headerlink}

    :   

    [[DNAA600L0001]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAA600L0001\']{.pre}*  (#mera.mera_platform.Platform.DNAA600L0001 "Link to this definition"){.headerlink}

    :   

    [[DNAA600L0002]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAA600L0002\']{.pre}*  (#mera.mera_platform.Platform.DNAA600L0002 "Link to this definition"){.headerlink}

    :   

    [[DNAF10032x2]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF10032x2\']{.pre}*  (#mera.mera_platform.Platform.DNAF10032x2 "Link to this definition"){.headerlink}

    :   

    [[DNAF100L0001]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF100L0001\']{.pre}*  (#mera.mera_platform.Platform.DNAF100L0001 "Link to this definition"){.headerlink}

    :   

    [[DNAF100L0002]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF100L0002\']{.pre}*  (#mera.mera_platform.Platform.DNAF100L0002 "Link to this definition"){.headerlink}

    :   

    [[DNAF100L0003]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF100L0003\']{.pre}*  (#mera.mera_platform.Platform.DNAF100L0003 "Link to this definition"){.headerlink}

    :   

    [[DNAF132S0001]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF132S0001\']{.pre}*  (#mera.mera_platform.Platform.DNAF132S0001 "Link to this definition"){.headerlink}

    :   

    [[DNAF200L0001]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF200L0001\']{.pre}*  (#mera.mera_platform.Platform.DNAF200L0001 "Link to this definition"){.headerlink}

    :   

    [[DNAF200L0002]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF200L0002\']{.pre}*  (#mera.mera_platform.Platform.DNAF200L0002 "Link to this definition"){.headerlink}

    :   

    [[DNAF200L0003]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF200L0003\']{.pre}*  (#mera.mera_platform.Platform.DNAF200L0003 "Link to this definition"){.headerlink}

    :   

    [[DNAF232S0001]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF232S0001\']{.pre}*  (#mera.mera_platform.Platform.DNAF232S0001 "Link to this definition"){.headerlink}

    :   

    [[DNAF232S0002]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF232S0002\']{.pre}*  (#mera.mera_platform.Platform.DNAF232S0002 "Link to this definition"){.headerlink}

    :   

    [[DNAF300L0001]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF300L0001\']{.pre}*  (#mera.mera_platform.Platform.DNAF300L0001 "Link to this definition"){.headerlink}

    :   

    [[DNAF632L0001]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF632L0001\']{.pre}*  (#mera.mera_platform.Platform.DNAF632L0001 "Link to this definition"){.headerlink}

    :   

    [[DNAF632L0002]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF632L0002\']{.pre}*  (#mera.mera_platform.Platform.DNAF632L0002 "Link to this definition"){.headerlink}

    :   

    [[DNAF632L0003]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAF632L0003\']{.pre}*  (#mera.mera_platform.Platform.DNAF632L0003 "Link to this definition"){.headerlink}

    :   

    [[MCU_CPU]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'ALT1\',]{.pre} [AccelKind.MCU)]{.pre}*  (#mera.mera_platform.Platform.MCU_CPU "Link to this definition"){.headerlink}

    :   

    [[MCU_ETHOS]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[(\'ALT2\',]{.pre} [AccelKind.MCU)]{.pre}*  (#mera.mera_platform.Platform.MCU_ETHOS "Link to this definition"){.headerlink}

    :   

    [[SAKURA_1]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAA600L0002\']{.pre}*  (#mera.mera_platform.Platform.SAKURA_1 "Link to this definition"){.headerlink}

    :   

    [[SAKURA_2]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAA600L0003\']{.pre}*  (#mera.mera_platform.Platform.SAKURA_2 "Link to this definition"){.headerlink}

    :   

    [[SAKURA_2C]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAA600L0003\']{.pre}*  (#mera.mera_platform.Platform.SAKURA_2C "Link to this definition"){.headerlink}

    :   

    [[SAKURA_I]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAA600L0002\']{.pre}*  (#mera.mera_platform.Platform.SAKURA_I "Link to this definition"){.headerlink}

    :   

    [[SAKURA_II]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DNAA600L0003\']{.pre}*  (#mera.mera_platform.Platform.SAKURA_II "Link to this definition"){.headerlink}

    :   

    *[property]{.pre}[ ]{.w}*[[accelerator_kind]{.pre}]{.sig-name .descname}  (#mera.mera_platform.Platform.accelerator_kind "Link to this definition"){.headerlink}

    :   

    *[property]{.pre}[ ]{.w}*[[platform_name]{.pre}]{.sig-name .descname}  (#mera.mera_platform.Platform.platform_name "Link to this definition"){.headerlink}

    :   


### mera.version module  

[[mera.version.]{.pre}]{.sig-prename .descclassname}[[get_mera2_rt_version]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[str]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.version.get_mera2_rt_version "Link to this definition"){.headerlink}

:   "return: The version string for mera2-runtime

 

[[mera.version.]{.pre}]{.sig-prename .descclassname}[[get_mera_dna_version]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[str]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.version.get_mera_dna_version "Link to this definition"){.headerlink}

:   Gets the version string for libmeradna

    Returns[:]{.colon}

    :   Summary of libmeradna version

 

[[mera.version.]{.pre}]{.sig-prename .descclassname}[[get_mera_tvm_version]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[str]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.version.get_mera_tvm_version "Link to this definition"){.headerlink}

:   Gets the version string for mera-tvm module

    Returns[:]{.colon}

    :   mera-tvm version

 

[[mera.version.]{.pre}]{.sig-prename .descclassname}[[get_mera_version]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[str]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.version.get_mera_version "Link to this definition"){.headerlink}

:   Gets the version string for Mera

    Returns[:]{.colon}

    :   Version string for Mera

 

[[mera.version.]{.pre}]{.sig-prename .descclassname}[[get_versions]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren} [[→]{.sig-return-icon} [[str]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.version.get_versions "Link to this definition"){.headerlink}

:   Return a summary of all installed modules on the Mera environment

    Returns[:]{.colon}

    :   List of all module's versions.


### mera.mera_quantizer module  

Mera Quantizer classes

*[class]{.pre}[ ]{.w}*[[mera.mera_quantizer.]{.pre}]{.sig-prename .descclassname}[[Quantizer]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[deployer]{.pre}]{.n}*, *[[model]{.pre}]{.n}*, *[[quantizer_config:]{.pre} [\~mera.quantizer.quantizer_config.QuantizerConfig]{.pre} [=]{.pre} [\<mera.quantizer.quantizer_config.QuantizerConfig]{.pre} [object\>]{.pre}]{.n}*, *[[mera_platform:]{.pre} [\~mera.mera_platform.Platform]{.pre} [=]{.pre} [Platform.SAKURA_2C]{.pre}]{.n}*, *[[\*\*kwargs]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_quantizer.Quantizer "Link to this definition"){.headerlink}

:   Bases: [`object`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    Class with API to quantize models using MERA

    [[apply_smoothquant]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[alpha]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[float]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[0.5]{.pre}]{.default_value}*, *[[autotune]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[bool]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[True]{.pre}]{.default_value}*[)]{.sig-paren}  (#mera.mera_quantizer.Quantizer.apply_smoothquant "Link to this definition"){.headerlink}

    :   

    [[calibrate]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[calibration_data]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[List]{.pre}[[\[]{.pre}]{.p}[Dict]{.pre}[[\[]{.pre}]{.p}[str]{.pre}[[,]{.pre}]{.p}[ ]{.w}[ndarray]{.pre}[[\]]{.pre}]{.p}[[\]]{.pre}]{.p}]{.n}*[)]{.sig-paren}  (#mera.mera_quantizer.Quantizer.calibrate "Link to this definition"){.headerlink}

    :   Feeds a series of realistic input data samples in order to be
        able to compute accurate internal ranges. MERA will collect the
        information from the execution of these data samples and compute
        the quantization domains as determined by the user
        configuration. It is recommended to use a big enough dataset of
        realistic samples in order to obtain the best quantization
        accuracy results.

        Parameters[:]{.colon}

        :   **calibration_data** -- List of dictionaries with the format
            {'input_name' : 'np_array'} containing the different data
            samples.

    [[evaluate_quality]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[evaluation_data]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[List]{.pre}[[\[]{.pre}]{.p}[Dict]{.pre}[[\[]{.pre}]{.p}[str]{.pre}[[,]{.pre}]{.p}[ ]{.w}[ndarray]{.pre}[[\]]{.pre}]{.p}[[\]]{.pre}]{.p}]{.n}*, *[[display_table]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[bool]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[True]{.pre}]{.default_value}*[)]{.sig-paren}  (#mera.mera_quantizer.Quantizer.evaluate_quality "Link to this definition"){.headerlink}

    :   Measures the quantization quality of a transformed model with a
        given evaluation data. This should be some realistic data
        sample(s) ideally different from the calibration dataset. In
        order to measure quality the user must have called quantize()
        method first.

        Parameters[:]{.colon}

        :   - **evaluation_data** -- List of dictionaries with the
              format {'input_name' : 'np_array'} containing the
              different data samples.

            - **display_table** -- Whether to display quality metrics to
              stdout or not.

        Returns[:]{.colon}

        :   List of quality metrics container.

    [[get_report]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[model_id]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_quantizer.Quantizer.get_report "Link to this definition"){.headerlink}

    :   Extracts all information about the quantization process as a
        dictionary that can be saved for debugging.

        Parameters[:]{.colon}

        :   **model_id** -- Identifier to be used for this document.

    [[quantize]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren}  (#mera.mera_quantizer.Quantizer.quantize "Link to this definition"){.headerlink}

    :   Uses the data gathered from the calibrate() method and creates a
        transformed model based on the quantizer configuration.

    [[reset]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren}  (#mera.mera_quantizer.Quantizer.reset "Link to this definition"){.headerlink}

    :   Resets all the internal observed metrics of the quantizer as
        well as any existing qtz transformed model.

    [[save_to]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[dst_path]{.pre}]{.n}*[)]{.sig-paren}  (#mera.mera_quantizer.Quantizer.save_to "Link to this definition"){.headerlink}

    :   Saves the transformed model to file. Must have called quantize()
        first. :param dst_path: Destination path where the model will be
        saved.

 

[[mera.mera_quantizer.]{.pre}]{.sig-prename .descclassname}[[get_input_desc]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[mera_model_path]{.pre}]{.n}*[)]{.sig-paren} [[→]{.sig-return-icon} [[InputDescriptionContainer]{.pre}]{.sig-return-typehint}]{.sig-return}  (#mera.mera_quantizer.get_input_desc "Link to this definition"){.headerlink}

:   Retrieve the input description of a MERA quantized model generated
    with MERA2.

    Parameters[:]{.colon}

    :   **mera_model_path** -- Path to .mera model file.

    Returns[:]{.colon}

    :   Dict with info about the model's inputs.


### mera.quantizer module  

MERA Quantizer Configuration classes.

*[class]{.pre}[ ]{.w}*[[mera.quantizer.quantizer_config.]{.pre}]{.sig-prename .descclassname}[[LayerConfig]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[conv_act]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[OperatorConfig]{.pre}](#mera.quantizer.quantizer_config.OperatorConfig "mera.quantizer.quantizer_config.OperatorConfig"){.reference .internal}]{.n}*, *[[conv_weights]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[OperatorConfig]{.pre}](#mera.quantizer.quantizer_config.OperatorConfig "mera.quantizer.quantizer_config.OperatorConfig"){.reference .internal}]{.n}*, *[[mm_act]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[OperatorConfig]{.pre}](#mera.quantizer.quantizer_config.OperatorConfig "mera.quantizer.quantizer_config.OperatorConfig"){.reference .internal}]{.n}*, *[[mm_weights]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[OperatorConfig]{.pre}](#mera.quantizer.quantizer_config.OperatorConfig "mera.quantizer.quantizer_config.OperatorConfig"){.reference .internal}]{.n}*[)]{.sig-paren}  (#mera.quantizer.quantizer_config.LayerConfig "Link to this definition"){.headerlink}

:   Bases: [`object`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    Set of quantization configurations to be applied for a Layer in the
    model

    *[property]{.pre}[ ]{.w}*[[conv_act]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[[OperatorConfig]{.pre}](#mera.quantizer.quantizer_config.OperatorConfig "mera.quantizer.quantizer_config.OperatorConfig"){.reference .internal}*  (#mera.quantizer.quantizer_config.LayerConfig.conv_act "Link to this definition"){.headerlink}

    :   

    *[property]{.pre}[ ]{.w}*[[conv_weights]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[[OperatorConfig]{.pre}](#mera.quantizer.quantizer_config.OperatorConfig "mera.quantizer.quantizer_config.OperatorConfig"){.reference .internal}*  (#mera.quantizer.quantizer_config.LayerConfig.conv_weights "Link to this definition"){.headerlink}

    :   

    *[property]{.pre}[ ]{.w}*[[mm_act]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[[OperatorConfig]{.pre}](#mera.quantizer.quantizer_config.OperatorConfig "mera.quantizer.quantizer_config.OperatorConfig"){.reference .internal}*  (#mera.quantizer.quantizer_config.LayerConfig.mm_act "Link to this definition"){.headerlink}

    :   

    *[property]{.pre}[ ]{.w}*[[mm_weights]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[[OperatorConfig]{.pre}](#mera.quantizer.quantizer_config.OperatorConfig "mera.quantizer.quantizer_config.OperatorConfig"){.reference .internal}*  (#mera.quantizer.quantizer_config.LayerConfig.mm_weights "Link to this definition"){.headerlink}

    :   

 

*[class]{.pre}[ ]{.w}*[[mera.quantizer.quantizer_config.]{.pre}]{.sig-prename .descclassname}[[ObserverClass]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[value]{.pre}]{.n}*[)]{.sig-paren}  (#mera.quantizer.quantizer_config.ObserverClass "Link to this definition"){.headerlink}

:   Bases: [`Enum`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    An enumeration.

    [[HISTOGRAM]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'HISTOGRAM\']{.pre}*  (#mera.quantizer.quantizer_config.ObserverClass.HISTOGRAM "Link to this definition"){.headerlink}

    :   An optimised \<min,max\> is calculated based on the distribution
        of the calibration data using a histogram. Can only be used
        PER_TENSOR.

    [[MAX_ABS]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'MAX_ABS\']{.pre}*  (#mera.quantizer.quantizer_config.ObserverClass.MAX_ABS "Link to this definition"){.headerlink}

    :   Will get the quantization range as \<-max(abs),max(abs)\> of the
        calibration data.

    [[MIN_MAX]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'MIN_MAX\']{.pre}*  (#mera.quantizer.quantizer_config.ObserverClass.MIN_MAX "Link to this definition"){.headerlink}

    :   Will get the quantization range as \<min,max\> based on the
        whole calibration data.

 

*[class]{.pre}[ ]{.w}*[[mera.quantizer.quantizer_config.]{.pre}]{.sig-prename .descclassname}[[OperatorConfig]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[qtype]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[QType]{.pre}](#mera.quantizer.quantizer_config.QType "mera.quantizer.quantizer_config.QType"){.reference .internal}]{.n}*, *[[qscheme]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[QScheme]{.pre}](#mera.quantizer.quantizer_config.QScheme "mera.quantizer.quantizer_config.QScheme"){.reference .internal}]{.n}*, *[[qmode]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[QMode]{.pre}](#mera.quantizer.quantizer_config.QMode "mera.quantizer.quantizer_config.QMode"){.reference .internal}]{.n}*, *[[qtarget]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[QTarget]{.pre}](#mera.quantizer.quantizer_config.QTarget "mera.quantizer.quantizer_config.QTarget"){.reference .internal}]{.n}*, *[[observer]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[ObserverClass]{.pre}](#mera.quantizer.quantizer_config.ObserverClass "mera.quantizer.quantizer_config.ObserverClass"){.reference .internal}]{.n}*, *[[\*\*]{.pre}]{.o}[[kwargs]{.pre}]{.n}*[)]{.sig-paren}  (#mera.quantizer.quantizer_config.OperatorConfig "Link to this definition"){.headerlink}

:   Bases: [`object`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    Set of quantizer configurations to be applied to an operator.

    *[property]{.pre}[ ]{.w}*[[observer]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[[ObserverClass]{.pre}](#mera.quantizer.quantizer_config.ObserverClass "mera.quantizer.quantizer_config.ObserverClass"){.reference .internal}*  (#mera.quantizer.quantizer_config.OperatorConfig.observer "Link to this definition"){.headerlink}

    :   

    *[property]{.pre}[ ]{.w}*[[qmode]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[[QMode]{.pre}](#mera.quantizer.quantizer_config.QMode "mera.quantizer.quantizer_config.QMode"){.reference .internal}*  (#mera.quantizer.quantizer_config.OperatorConfig.qmode "Link to this definition"){.headerlink}

    :   

    *[property]{.pre}[ ]{.w}*[[qscheme]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[[QScheme]{.pre}](#mera.quantizer.quantizer_config.QScheme "mera.quantizer.quantizer_config.QScheme"){.reference .internal}*  (#mera.quantizer.quantizer_config.OperatorConfig.qscheme "Link to this definition"){.headerlink}

    :   

    *[property]{.pre}[ ]{.w}*[[qtarget]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[[QTarget]{.pre}](#mera.quantizer.quantizer_config.QTarget "mera.quantizer.quantizer_config.QTarget"){.reference .internal}*  (#mera.quantizer.quantizer_config.OperatorConfig.qtarget "Link to this definition"){.headerlink}

    :   

    *[property]{.pre}[ ]{.w}*[[qtype]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[[QType]{.pre}](#mera.quantizer.quantizer_config.QType "mera.quantizer.quantizer_config.QType"){.reference .internal}*  (#mera.quantizer.quantizer_config.OperatorConfig.qtype "Link to this definition"){.headerlink}

    :   

    [[set_options]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[histogram_n_bins]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*, *[[histogram_obs_upsample_rate]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*, *[[per_channel_limit]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*, *[[per_channel_grp_size]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*, *[[use_symmetric_range]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[bool]{.pre}[ ]{.w}[[\|]{.pre}]{.p}[ ]{.w}[None]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[None]{.pre}]{.default_value}*[)]{.sig-paren}  (#mera.quantizer.quantizer_config.OperatorConfig.set_options "Link to this definition"){.headerlink}

    :   Sets advanced quantization options for this operator.

        Parameters[:]{.colon}

        :   - **histogram_n_bins** -- When using histogram observer,
              overrides default number of bins used.

            - **histogram_upsample_rate** -- When using histogram
              observer, overrides default upsample rate for histogram
              aggregations.

            - **per_channel_limit** -- Architecture limitation to mark
              the maximum number of channels of a tensor possible where
              PER_CHANNEL quantization can still be done. Any operation
              above this limit will switch to use PER_CHANNEL_GROUP
              instead.

            - **per_channel_grp_size** -- When using PER_CHANNEL_GROUP,
              specifies the max size of q_params that will group all the
              channels in a tensor.

            - **use_symmetric_range** -- Reduces the range of
              quantization so that values are set in \<-MaxVal,MaxVal\>.
              e.g. \[-127,127\] for int8 type. Only valid for the case
              of signed quantization.

 

*[class]{.pre}[ ]{.w}*[[mera.quantizer.quantizer_config.]{.pre}]{.sig-prename .descclassname}[[QMode]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[value]{.pre}]{.n}*[)]{.sig-paren}  (#mera.quantizer.quantizer_config.QMode "Link to this definition"){.headerlink}

:   Bases: [`Enum`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    An enumeration.

    [[PER_CHANNEL]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'PER_CHANNEL\']{.pre}*  (#mera.quantizer.quantizer_config.QMode.PER_CHANNEL "Link to this definition"){.headerlink}

    :   A different set of \<scale,zero_point\> for each of the tensor's
        channels.

    [[PER_CHANNEL_GROUP]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'PER_CHANNEL_GROUP\']{.pre}*  (#mera.quantizer.quantizer_config.QMode.PER_CHANNEL_GROUP "Link to this definition"){.headerlink}

    :   A different set of \<scale,zero_point\> for each group of
        several tensor's channels.

    [[PER_TENSOR]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'PER_TENSOR\']{.pre}*  (#mera.quantizer.quantizer_config.QMode.PER_TENSOR "Link to this definition"){.headerlink}

    :   Single set of \<scale,zero_point\> for the whole tensor.

 

*[class]{.pre}[ ]{.w}*[[mera.quantizer.quantizer_config.]{.pre}]{.sig-prename .descclassname}[[QScheme]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[value]{.pre}]{.n}*[)]{.sig-paren}  (#mera.quantizer.quantizer_config.QScheme "Link to this definition"){.headerlink}

:   Bases: [`Enum`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    An enumeration.

    [[AFFINE]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'AFFINE\']{.pre}*  (#mera.quantizer.quantizer_config.QScheme.AFFINE "Link to this definition"){.headerlink}

    :   Quantization range adjusted to observed \<min,max\> from data

    [[SYMMETRIC]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'SYMMETRIC\']{.pre}*  (#mera.quantizer.quantizer_config.QScheme.SYMMETRIC "Link to this definition"){.headerlink}

    :   Quantization range centered around real value 0.

 

*[class]{.pre}[ ]{.w}*[[mera.quantizer.quantizer_config.]{.pre}]{.sig-prename .descclassname}[[QTarget]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[value]{.pre}]{.n}*[)]{.sig-paren}  (#mera.quantizer.quantizer_config.QTarget "Link to this definition"){.headerlink}

:   Bases: [`Enum`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    An enumeration.

    [[DATA]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'DATA\']{.pre}*  (#mera.quantizer.quantizer_config.QTarget.DATA "Link to this definition"){.headerlink}

    :   Tensor representing the activated data of a quantizable
        operation.

    [[WEIGHT]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'WEIGHT\']{.pre}*  (#mera.quantizer.quantizer_config.QTarget.WEIGHT "Link to this definition"){.headerlink}

    :   Tensor are the weights of a quantizable operation.

 

*[class]{.pre}[ ]{.w}*[[mera.quantizer.quantizer_config.]{.pre}]{.sig-prename .descclassname}[[QType]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[value]{.pre}]{.n}*[)]{.sig-paren}  (#mera.quantizer.quantizer_config.QType "Link to this definition"){.headerlink}

:   Bases: [`Enum`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    An enumeration.

    [[BF16]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'BF16\']{.pre}*  (#mera.quantizer.quantizer_config.QType.BF16 "Link to this definition"){.headerlink}

    :   Unquantized BrainFloat16 type.

    [[S7]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'S7\']{.pre}*  (#mera.quantizer.quantizer_config.QType.S7 "Link to this definition"){.headerlink}

    :   7-bit signed, ranged \[-64, 63\]

    [[S8]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'S8\']{.pre}*  (#mera.quantizer.quantizer_config.QType.S8 "Link to this definition"){.headerlink}

    :   8-bit signed, ranged \[-128, 127\]

    [[U7]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'U7\']{.pre}*  (#mera.quantizer.quantizer_config.QType.U7 "Link to this definition"){.headerlink}

    :   7-bit unsigned, ranged \[0, 127\]

    [[U8]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\'U8\']{.pre}*  (#mera.quantizer.quantizer_config.QType.U8 "Link to this definition"){.headerlink}

    :   8-bit unsigned, ranged \[0, 255\]

 

*[class]{.pre}[ ]{.w}*[[mera.quantizer.quantizer_config.]{.pre}]{.sig-prename .descclassname}[[QuantizerConfig]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[global_cfg]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[[LayerConfig]{.pre}](#mera.quantizer.quantizer_config.LayerConfig "mera.quantizer.quantizer_config.LayerConfig"){.reference .internal}]{.n}*, *[[flow_version]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[int]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[1]{.pre}]{.default_value}*[)]{.sig-paren}  (#mera.quantizer.quantizer_config.QuantizerConfig "Link to this definition"){.headerlink}

:   Bases: [`object`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    Class representing the configuration of the MERA quantizer.

    [[to_dict]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren}  (#mera.quantizer.quantizer_config.QuantizerConfig.to_dict "Link to this definition"){.headerlink}

    :   

    *[property]{.pre}[ ]{.w}*[[transform_cfg]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[[TransformConfig]{.pre}](#mera.quantizer.quantizer_config.TransformConfig "mera.quantizer.quantizer_config.TransformConfig"){.reference .internal}*  (#mera.quantizer.quantizer_config.QuantizerConfig.transform_cfg "Link to this definition"){.headerlink}

    :   

 

*[class]{.pre}[ ]{.w}*[[mera.quantizer.quantizer_config.]{.pre}]{.sig-prename .descclassname}[[QuantizerConfigPresets]{.pre}]{.sig-name .descname}  (#mera.quantizer.quantizer_config.QuantizerConfigPresets "Link to this definition"){.headerlink}

:   Bases: [`object`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    [[ALT]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\<mera.quantizer.quantizer_config.QuantizerConfig]{.pre} [object\>]{.pre}*  (#mera.quantizer.quantizer_config.QuantizerConfigPresets.ALT "Link to this definition"){.headerlink}

    :   

    [[DEFAULT]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\<mera.quantizer.quantizer_config.QuantizerConfig]{.pre} [object\>]{.pre}*  (#mera.quantizer.quantizer_config.QuantizerConfigPresets.DEFAULT "Link to this definition"){.headerlink}

    :   Sample base configuration for DNA quantizations.

    [[DNA_SAKURA_II]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\<mera.quantizer.quantizer_config.QuantizerConfig]{.pre} [object\>]{.pre}*  (#mera.quantizer.quantizer_config.QuantizerConfigPresets.DNA_SAKURA_II "Link to this definition"){.headerlink}

    :   

    [[MCU]{.pre}]{.sig-name .descname}*[ ]{.w}[[=]{.pre}]{.p}[ ]{.w}[\<mera.quantizer.quantizer_config.QuantizerConfig]{.pre} [object\>]{.pre}*  (#mera.quantizer.quantizer_config.QuantizerConfigPresets.MCU "Link to this definition"){.headerlink}

    :   Sample base configuration for MCU quantizations.

 

*[class]{.pre}[ ]{.w}*[[mera.quantizer.quantizer_config.]{.pre}]{.sig-prename .descclassname}[[TransformConfig]{.pre}]{.sig-name .descname}  (#mera.quantizer.quantizer_config.TransformConfig "Link to this definition"){.headerlink}

:   Bases: [`object`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    Class representing options for transformation of model into
    quantized MERA model.

    *[property]{.pre}[ ]{.w}*[[fuse_i8_concat_domains]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[bool]{.pre}*  (#mera.quantizer.quantizer_config.TransformConfig.fuse_i8_concat_domains "Link to this definition"){.headerlink}

    :   

    *[property]{.pre}[ ]{.w}*[[glu_bf16_outlier_threshold]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[float]{.pre}*  (#mera.quantizer.quantizer_config.TransformConfig.glu_bf16_outlier_threshold "Link to this definition"){.headerlink}

    :   

    *[property]{.pre}[ ]{.w}*[[map_silu_to_hswish]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[bool]{.pre}*  (#mera.quantizer.quantizer_config.TransformConfig.map_silu_to_hswish "Link to this definition"){.headerlink}

    :   

    *[property]{.pre}[ ]{.w}*[[use_bf16_for_small_ch_conv]{.pre}]{.sig-name .descname}*[[:]{.pre}]{.p}[ ]{.w}[bool]{.pre}*  (#mera.quantizer.quantizer_config.TransformConfig.use_bf16_for_small_ch_conv "Link to this definition"){.headerlink}

    :   

Wrapper class for quantizer quality objects

*[class]{.pre}[ ]{.w}*[[mera.quantizer.quality.]{.pre}]{.sig-prename .descclassname}[[QuantizationQuality]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[data]{.pre}]{.n}*, *[[out_names]{.pre}]{.n}*[)]{.sig-paren}  (#mera.quantizer.quality.QuantizationQuality "Link to this definition"){.headerlink}

:   Bases: [`object`{.xref .py .py-class .docutils .literal
    .notranslate}]{.pre}

    Container class that holds different quality metrics of a quantized
    tensor.

    [[node_summary]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren}  (#mera.quantizer.quality.QuantizationQuality.node_summary "Link to this definition"){.headerlink}

    :   Returns a metric summary of the intermediate nodes of the model.

    [[out_summary]{.pre}]{.sig-name .descname}[(]{.sig-paren}[)]{.sig-paren}  (#mera.quantizer.quality.QuantizationQuality.out_summary "Link to this definition"){.headerlink}

    :   Returns a metric summary of the outputs of the model.

    [[to_table]{.pre}]{.sig-name .descname}[(]{.sig-paren}*[[extra_debug_info]{.pre}]{.n}[[:]{.pre}]{.p}[ ]{.w}[[bool]{.pre}]{.n}[ ]{.w}[[=]{.pre}]{.o}[ ]{.w}[[False]{.pre}]{.default_value}*[)]{.sig-paren}  (#mera.quantizer.quality.QuantizationQuality.to_table "Link to this definition"){.headerlink}

    :   Returns a tabulated table representation of the data

